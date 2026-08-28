#!/usr/bin/env python3
"""Find function boundaries in an overlay without relying on the wiki.

The FFHacktics routine listings are the candidate source for FAST MODE, but they
only cover part of each overlay. WORLD.BIN, WLDCORE.BIN and the main executable
are catalogued thinly enough that matching every named routine still leaves them
far short of 25% coverage, so raising those modules requires finding functions
nobody has named.

Detection is deliberately conservative and evidence-based rather than clever:

  * A function ends at `jr $ra` (0x03e00008) plus its delay slot. This is exact.
  * A function starts at the first instruction after the previous function's
    end, skipping alignment padding (`nop` runs).
  * A leaf function that never touches `$sp` is still bounded correctly by the
    rule above, so no prologue heuristic is needed to find boundaries -- only to
    sanity-check them.

Everything the detector emits is checked against config/modules.yaml: every
address we have already reconstructed MUST be rediscovered, and any disagreement
about a known function's size is reported. That is the whole reason to trust the
output on the ranges we have not reconstructed yet.

Usage:
    python3 scripts/discover_functions.py --module world --validate
    python3 scripts/discover_functions.py --module world --emit-pool > pool.txt
"""
import argparse, re, struct, sys, os

# Routine-listing pages, mirrored from scripts/coverage.py. Used only to bound
# the executable region of an overlay, never to decide a function boundary.
ROUTINE_PAGES = {
    'battle':         'original/ffhacktics/wiki/pages/00000161.wiki',
    'world':          'original/ffhacktics/wiki/pages/00000836.wiki',
    'wldcore':        'original/ffhacktics/wiki/pages/00000837.wiki',
    'opening':        'original/ffhacktics/wiki/pages/00007311.wiki',
    'event-attack':   'original/ffhacktics/wiki/pages/00009425.wiki',
    'event-etc':      'original/ffhacktics/wiki/pages/00009424.wiki',
    'event-helpmenu': 'original/ffhacktics/wiki/pages/00010918.wiki',
    'event-bunit':    'original/ffhacktics/wiki/pages/00009927.wiki',
    'event-card':     'original/ffhacktics/wiki/pages/00010822.wiki',
    'event-debugchr': 'original/ffhacktics/wiki/pages/00010925.wiki',
    'event-equip':    'original/ffhacktics/wiki/pages/00002339.wiki',
    'event-jobstts':  'original/ffhacktics/wiki/pages/00010007.wiki',
    'event-option':   'original/ffhacktics/wiki/pages/00010803.wiki',
    'event-require':  'original/ffhacktics/wiki/pages/00009423.wiki',
    'main':           'original/ffhacktics/scus_94221_routines.wiki.txt',
}

JR_RA = 0x03E00008
NOP = 0x00000000

# `addiu $sp, $sp, -N` -- the conventional non-leaf prologue. Used only as a
# corroborating signal in --validate, never to decide a boundary.
def is_sp_adjust(word):
    if (word & 0xFFFF0000) != 0x27BD0000:
        return False
    imm = word & 0xFFFF
    return imm >= 0x8000          # negative immediate: allocating a frame


def load_module(mid):
    """(bytes, load_address, file_bias) for a module in modules.yaml."""
    text = open('config/modules.yaml').read()
    blocks = re.split(r'\n  - id: ', text)
    for b in blocks:
        if not b.startswith(mid + '\n'):
            continue
        disc = re.search(r'disc_path:\s*(\S+)', b)
        la = re.search(r'load_address:\s*"(0x[0-9a-fA-F]+)"', b)
        cls = re.search(r'classification:\s*(\S+)', b)
        if not (disc and la):
            raise SystemExit(f"module {mid}: missing disc_path/load_address")
        path = os.path.join('build/extracted/files', disc.group(1))
        if not os.path.exists(path):
            raise SystemExit(f"extracted file not found: {path} (run make bootstrap)")
        bias = 0x800 if (cls and cls.group(1) == 'ps-x-exe') else 0
        return open(path, 'rb').read(), int(la.group(1), 16), bias
    raise SystemExit(f"module {mid} not found in modules.yaml")


def known_functions(mid):
    """{address: bytes} already reconstructed for this module."""
    out = {}
    text = open('config/modules.yaml').read()
    cur = None
    for line in text.splitlines():
        m = re.match(r'\s*-\s+id:\s*(\S+)', line)
        if m:
            cur = m.group(1)
            continue
        if cur != mid:
            continue
        a = re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
        b = re.search(r'\bbytes:\s*(\d+)', line)
        if a and b:
            out[int(a.group(1), 16)] = int(b.group(1))
    return out


def library_ranges(mid):
    """[(start, end_exclusive, id)] of linked library code owned by this module.

    AGENTS.md excludes Sony library and middleware code from reconstruction, and
    `config/libraries.yaml` already records those ownership ranges. Without this
    filter the detector happily emits them: an early discovered batch was 75%
    LIBCD/LIBGPU getters, which a worker then had to identify and reject by hand.
    """
    path = 'config/libraries.yaml'
    if not os.path.exists(path):
        return []
    text = open(path).read()
    owner = re.search(r'^module_id:\s*(\S+)', text, re.M)
    if not owner or owner.group(1) != mid:
        return []
    out = []
    for blk in re.split(r'\n  - id: ', text)[1:]:
        rid = blk.split('\n', 1)[0].strip()
        a = re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', blk)
        e = re.search(r'(?<![\w])end:\s*"(0x[0-9a-fA-F]+)"', blk)
        if a and e:
            out.append((int(a.group(1), 16), int(e.group(1), 16), rid))
    return out


def bound_symbols(mid):
    """Addresses already bound to a name in linker-symbols.yaml for this module.

    A discovered range that is already a known extern (e.g. `GetGraphType`) is
    library code we link against, not something to reconstruct.
    """
    path = 'config/linker-symbols.yaml'
    if not os.path.exists(path):
        return {}
    out = {}
    cur = None
    for line in open(path):
        # Blocks are headed `- id: <module>`; bindings use either quote style.
        m = re.match(r'\s*-\s*id:\s*(\S+)', line)
        if m:
            cur = m.group(1)
            continue
        if cur != mid:
            continue
        m = re.match(r'''\s*(\w+):\s*['"](0x[0-9a-fA-F]+)['"]''', line)
        if m:
            out[int(m.group(2), 16)] = m.group(1)
    return out


def code_extent(mid, known):
    """(lo, hi) bounding the module's executable region, or (None, None).

    Taken from the module's FFHacktics routine-listing page -- the same source
    `scripts/coverage.py` uses for its denominator -- and widened to cover every
    address we have already reconstructed.

    This bound matters more than it looks. An overlay file is mostly data, and
    the word 0x03e00008 shows up in graphics and tables often enough to
    manufacture plausible-looking "functions" by the hundred. Without it,
    EVENT/HELPMENU.OUT yields 99,576 bytes of candidates against a 5,592-byte
    code region.
    """
    page = ROUTINE_PAGES.get(mid)
    lo = hi = None
    if page and os.path.exists(page):
        rex = re.compile(
            r'^\s*\[?\[?([0-9a-fA-F]{6,8})\s*-\s*([0-9a-fA-F]{6,8})\]?\]?:')
        for line in open(page, errors='replace'):
            m = rex.match(line)
            if not m:
                continue
            a = int(m.group(1), 16) | 0x80000000
            e = (int(m.group(2), 16) | 0x80000000) + 4
            if e < a or e - a > 0x20000:
                continue
            lo = a if lo is None else min(lo, a)
            hi = e if hi is None else max(hi, e)
    for a, n in known.items():
        lo = a if lo is None else min(lo, a)
        hi = a + n if hi is None else max(hi, a + n)
    return lo, hi


def jal_targets(words, load_address, bias, lo, hi):
    """Addresses called by a `jal` anywhere in the image.

    A `jal` target is an authoritative function entry point, which is what makes
    it possible to tell an early `return` apart from the end of a function: a
    `jr $ra` followed by more code is only a boundary if something actually calls
    the code that follows.
    """
    out = set()
    for w in words:
        if (w >> 26) != 0x03:                  # jal
            continue
        # The target's top nibble comes from the delay slot's address; every
        # overlay here lives inside one 256MB region, so load_address supplies it.
        t = ((load_address & 0xF0000000) | ((w & 0x03FFFFFF) << 2))
        if lo <= t < hi:
            out.add(t)
    return out


def discover(data, load_address, bias, extra_starts=()):
    """[(start_addr, end_addr_exclusive)] for every function in the image.

    Ends are `jr $ra` plus its delay slot; starts are the next non-padding word.

    A tempting refinement is to treat a `jr $ra` as a boundary only when
    something demonstrably calls the code that follows (a `jal` target), on the
    theory that an early `return` would otherwise split one function in two.
    That was tried and is measurably worse: it merges every function reached
    only indirectly or by tail call, and on BATTLE.BIN it produced a single
    "function" of 342,668 bytes. Size disagreements against known
    reconstructions went from 1 to 48.

    The simple rule wins because GCC 2.6.3 almost always merges returns into a
    single epilogue. It is kept, with one addition: an address already known to
    be a function start forces a boundary, which recovers the handful of cases
    where a real early return does appear.
    """
    n = len(data) // 4
    words = struct.unpack_from('<%dI' % n, data, 0)
    forced = set(extra_starts)

    funcs = []
    start_i = None
    i = 0
    while i < n:
        addr = load_address + i * 4 - bias
        w = words[i]
        if start_i is None:
            if w == NOP:
                i += 1
                continue                      # alignment padding between funcs
            start_i = i
        elif addr in forced and i != start_i:
            # A known entry point inside what we thought was one function: the
            # preceding `jr $ra` was a real early return, so close here.
            funcs.append((load_address + start_i * 4 - bias, addr))
            start_i = i
        if w == JR_RA:
            end_i = i + 2                     # include the delay slot
            funcs.append((load_address + start_i * 4 - bias,
                          load_address + end_i * 4 - bias))
            start_i = None
            i = end_i
            continue
        i += 1
    if start_i is not None:                    # trailing code with no `jr $ra`
        funcs.append((load_address + start_i * 4 - bias,
                      load_address + n * 4 - bias))
    return funcs


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--module', required=True)
    p.add_argument('--validate', action='store_true',
                   help='check detected boundaries against known reconstructions')
    p.add_argument('--emit-pool', action='store_true',
                   help='print undiscovered candidates as pool TSV rows')
    p.add_argument('--min-size', type=int, default=12)
    p.add_argument('--max-size', type=int, default=800)
    args = p.parse_args()

    data, la, bias = load_module(args.module)
    known = known_functions(args.module)
    # Seed with addresses we have already reconstructed: they are known-good
    # entry points and cost nothing to supply.
    funcs = discover(data, la, bias, extra_starts=set(known))

    if args.validate:
        found = {s: e - s for s, e in funcs}
        missing = [a for a in known if a not in found]
        wrong = [(a, known[a], found[a]) for a in known
                 if a in found and found[a] != known[a]]
        print(f"module {args.module}: {len(funcs)} functions detected, "
              f"{len(known)} already reconstructed")
        print(f"  known addresses rediscovered : {len(known) - len(missing)}/{len(known)}")
        print(f"  size disagreements           : {len(wrong)}")
        for a in sorted(missing)[:10]:
            print(f"    MISSED  0x{a:08x} ({known[a]} bytes)")
        for a, k, f in sorted(wrong)[:10]:
            print(f"    SIZE    0x{a:08x} known={k} detected={f}")
        if missing or wrong:
            print("\n  Treat the pool as advisory until these are understood.")
        else:
            print("\n  Detector agrees with every known reconstruction.")
        return

    if args.emit_pool:
        libs = library_ranges(args.module)
        bound = bound_symbols(args.module)
        code_lo, code_hi = code_extent(args.module, known)
        skipped_lib = skipped_outside = 0
        for s, e in funcs:
            size = e - s
            if s in known or not (args.min_size <= size <= args.max_size):
                continue
            if code_lo is not None and not (code_lo <= s < code_hi):
                # Outside the module's known code region. An overlay file holds
                # graphics and tables as well as code, and `jr $ra` occurs in
                # data by coincidence often enough to manufacture hundreds of
                # bogus "functions" -- EVENT/HELPMENU.OUT reported 99,576 bytes
                # of them against a 5,592-byte code region.
                skipped_outside += 1
                continue
            if any(lo <= s < hi for lo, hi, _ in libs) or s in bound:
                skipped_lib += 1
                continue
            # Unnamed by construction: the symbol is provisional and a worker
            # must rename it from behaviour before promotion.
            print(f"{args.module}\t{size}\t0x{s:08x}\t0x{e:08x}\tfunc_{s:08x}")
        if skipped_outside:
            print(f"# excluded {skipped_outside} candidates outside the "
                  f"module's known code region", file=sys.stderr)
        if skipped_lib:
            print(f"# excluded {skipped_lib} candidates owned by "
                  f"config/libraries.yaml or already bound in "
                  f"config/linker-symbols.yaml", file=sys.stderr)


if __name__ == '__main__':
    main()
