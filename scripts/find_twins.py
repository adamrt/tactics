#!/usr/bin/env python3
"""Find byte-identical (modulo relocation) twins of placeholder-named functions.

Many functions exist in more than one overlay: WORLD.BIN and BATTLE.BIN share a
large body of code, and the EVENT/*.OUT menu overlays are built from the same
sources with different link addresses. When one copy has already been named
from its behaviour and another copy is still `func_<addr>`, the name can be
carried across -- provided the two bodies really are the same code.

This tool computes a masked signature for every `status: matching`
reconstruction in the requested modules, groups equal signatures, and reports
every group that contains at least one placeholder-named function and at least
one real-named one.

Two signature modes, two evidence tiers
---------------------------------------

strict  Masks ONLY the fields that the linker relocates, so that two functions
        compare equal iff they are the same instruction stream linked at
        different addresses:
          * the 26-bit target of `j` / `jal`
          * the 16-bit immediate of `lui`, `addiu`, `ori` (hi/lo address
            construction)
          * the 16-bit offset of every load/store: lw lh lhu lb lbu sw sh sb
            lwl lwr swl swr
        Every opcode, register field, shift amount, branch offset and
        arithmetic/logic constant (slti, andi, xori, addi, ...) must still be
        identical. Note that this also masks non-address addiu/ori constants
        (e.g. frame sizes, `addiu v0,zero,N`), because the encoding does not
        say which addiu is an address and which is a plain constant; branch
        offsets and comparison constants are NOT masked, which is enough to
        keep the structure and almost all constants pinned. A strict match is
        strong evidence of identity: same control flow, same register
        allocation, same comparisons.

loose   Additionally masks ALL 16-bit immediates of every I-type instruction:
        branch offsets (beq/bne/blez/bgtz/bltz/bgez and the *al forms),
        addi/slti/sltiu/andi/xori constants, and cop1/cop2 load/store offsets.
        Two functions with equal loose signatures have the same sequence of
        opcodes and register fields, but may branch different distances and
        compare against different constants. That is the same *shape* -- often
        the same source with a different table size or struct offset -- but it
        is also what two unrelated small helpers can look like (e.g. any two
        `return field == K` accessors). Loose is therefore weaker evidence and
        must be confirmed by reading both bodies before a name is copied.

Output
------
TSV, one row per (placeholder, twin) pair:

    placeholder  candidate_name  strict|loose  twin_symbol  twin_module

`candidate_name` is the twin's name re-prefixed with the placeholder module's
convention (battle_/world_/wldcore_/<overlay>_/open_; `main` has no prefix).
A pair is reported as loose only when it is not already a strict match.

Caveat for small functions: a three-instruction `jal X; nop; jr ra` wrapper or
a `sw v,K(gp-ish global)` setter strict-matches EVERY other wrapper/setter,
because the only field that distinguished them was masked. Such a group tells
you the placeholder is a wrapper, not which one. `--agree` drops every group
whose real-named members do not all share one base name, which removes that
noise and leaves the matches that actually carry a name.

Usage:
    python3 scripts/find_twins.py battle world wldcore
    python3 scripts/find_twins.py event-bunit event-attack event-equip ... --min-bytes 16
    python3 scripts/find_twins.py --all-event battle world wldcore --agree
"""
import argparse
import collections
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
MODULES_YAML = os.path.join(ROOT, 'config', 'modules.yaml')
EXTRACTED = os.path.join(ROOT, 'build', 'extracted', 'files')

PLACEHOLDER_RE = re.compile(
    r'^func_|_8[0-9a-f]{7}$|_out_[0-9a-f]{8}_[0-9a-f]{8}$|_func_8')

# --- opcode classes -------------------------------------------------------

OP_J, OP_JAL = 0x02, 0x03
OP_LUI, OP_ADDIU, OP_ORI = 0x0F, 0x09, 0x0D
OP_LOADSTORE = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26,   # lb lh lwl lw lbu lhu lwr
                0x28, 0x29, 0x2A, 0x2B, 0x2E}               # sb sh swl sw swr
STRICT_IMM16 = {OP_LUI, OP_ADDIU, OP_ORI} | OP_LOADSTORE
# Every I-type opcode with a 16-bit immediate/offset (loose adds these).
LOOSE_IMM16 = STRICT_IMM16 | {
    0x01,                       # REGIMM: bltz/bgez/bltzal/bgezal
    0x04, 0x05, 0x06, 0x07,     # beq bne blez bgtz
    0x08, 0x0A, 0x0B, 0x0C, 0x0E,   # addi slti sltiu andi xori
    0x31, 0x32, 0x39, 0x3A,     # lwc1 lwc2 swc1 swc2
}


def signature(data, mode):
    """Bytes of `data` with relocatable/immediate fields zeroed per `mode`."""
    imm16 = STRICT_IMM16 if mode == 'strict' else LOOSE_IMM16
    n = len(data) // 4
    words = list(struct.unpack('<%dI' % n, data[:n * 4]))
    out = []
    for w in words:
        op = w >> 26
        if op == OP_J or op == OP_JAL:
            w &= 0xFC000000
        elif op in imm16:
            w &= 0xFFFF0000
        out.append(w)
    return struct.pack('<%dI' % n, *out) + data[n * 4:]


# --- modules.yaml ---------------------------------------------------------

def parse_range(s):
    a, b = s.strip().strip('"').split('-')
    return int(a, 16), int(b, 16)


def _record_from_flow(line):
    body = line[line.index('{') + 1:line.rindex('}')]
    rec = {}
    for kv in body.split(','):
        if ':' not in kv:
            continue
        k, v = kv.split(':', 1)
        rec[k.strip()] = v.strip().strip('"')
    return rec


def load_modules():
    """{module_id: {'disc_path':..., 'recs': [ {symbol,file_range,status,address}, ...]}}"""
    text = open(MODULES_YAML).read()
    mods = {}
    cur = None
    in_recs = False
    block = None
    for line in text.splitlines():
        m = re.match(r'  - id:\s*(\S+)', line)
        if m:
            cur = {'id': m.group(1), 'disc_path': None, 'recs': []}
            mods[cur['id']] = cur
            in_recs = False
            block = None
            continue
        if cur is None:
            continue
        m = re.match(r'    disc_path:\s*(\S+)', line)
        if m:
            cur['disc_path'] = m.group(1)
            continue
        if re.match(r'    reconstructions:', line):
            in_recs = True
            block = None
            continue
        if re.match(r'    \S', line):          # another top-level key of the module
            in_recs = False
            block = None
            continue
        if not in_recs:
            continue
        s = line.strip()
        if s.startswith('- {'):
            cur['recs'].append(_record_from_flow(line))
            block = None
        elif s.startswith('- '):
            block = {}
            cur['recs'].append(block)
            k, v = s[2:].split(':', 1)
            block[k.strip()] = v.strip().strip('"')
        elif block is not None and ':' in s and not s.startswith('-'):
            k, v = s.split(':', 1)
            block[k.strip()] = v.strip().strip('"')
    return mods


def module_prefix(mid):
    if mid == 'main':
        return ''
    if mid == 'opening':
        return 'open_'
    if mid.startswith('event-'):
        return mid[len('event-'):] + '_'
    return mid + '_'


def reprefix(name, from_mid, to_mid):
    src, dst = module_prefix(from_mid), module_prefix(to_mid)
    base = name[len(src):] if src and name.startswith(src) else name
    return dst + base


def collect(mods, mid, min_bytes):
    """[(symbol, module, data)] for matching reconstructions of `mid`."""
    if mid not in mods:
        raise SystemExit(f"module {mid} not in modules.yaml")
    m = mods[mid]
    path = os.path.join(EXTRACTED, m['disc_path'])
    if not os.path.exists(path):
        raise SystemExit(f"extracted file not found: {path} (run make bootstrap)")
    blob = open(path, 'rb').read()
    out = []
    for r in m['recs']:
        if r.get('status') != 'matching' or 'file_range' not in r:
            continue
        a, b = parse_range(r['file_range'])
        data = blob[a:b + 1]
        if len(data) < min_bytes:
            continue
        out.append((r['symbol'], mid, data))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    ap.add_argument('modules', nargs='*', help='module ids from config/modules.yaml')
    ap.add_argument('--all-event', action='store_true', help='add every event-* module')
    ap.add_argument('--min-bytes', type=int, default=0,
                    help='ignore functions smaller than this (tiny stubs twin everything)')
    ap.add_argument('--mode', choices=['strict', 'loose', 'both'], default='both')
    ap.add_argument('--all-groups', action='store_true',
                    help='also list groups with no placeholder (debugging)')
    ap.add_argument('--agree', action='store_true',
                    help='only report groups whose real-named members all share one '
                         'base name; a group of setters/wrappers with N different names '
                         'proves the placeholder is a setter/wrapper, not which one')
    args = ap.parse_args()

    mods = load_modules()
    mids = list(args.modules)
    if args.all_event:
        mids += sorted(k for k in mods if k.startswith('event-') and k not in mids)
    if not mids:
        ap.error('no modules given')

    funcs = []
    for mid in mids:
        funcs += collect(mods, mid, args.min_bytes)

    groups = {}
    for mode in ('strict', 'loose'):
        g = collections.defaultdict(list)
        for sym, mid, data in funcs:
            g[signature(data, mode)].append((sym, mid))
        groups[mode] = g

    strict_pairs = set()
    rows = []
    modes = ['strict', 'loose'] if args.mode == 'both' else [args.mode]
    for mode in modes:
        for sig, members in groups[mode].items():
            if len(members) < 2:
                continue
            ph = [x for x in members if PLACEHOLDER_RE.search(x[0])]
            real = [x for x in members if not PLACEHOLDER_RE.search(x[0])]
            if args.all_groups and not ph:
                for a in members:
                    for b in members:
                        if a != b:
                            rows.append((a[0], reprefix(b[0], b[1], a[1]), mode, b[0], b[1]))
                continue
            if not ph or not real:
                continue
            if args.agree:
                bases = {reprefix(s, m, 'main') for s, m in real}
                if len(bases) > 1:
                    continue
            for p_sym, p_mid in ph:
                for r_sym, r_mid in real:
                    key = (p_sym, p_mid, r_sym, r_mid)
                    if mode == 'strict':
                        strict_pairs.add(key)
                    elif key in strict_pairs:
                        continue
                    rows.append((p_sym, reprefix(r_sym, r_mid, p_mid), mode, r_sym, r_mid))

    for row in rows:
        print('\t'.join(row))
    print(f"# {len(funcs)} functions from {len(mids)} modules; "
          f"{sum(1 for r in rows if r[2]=='strict')} strict rows, "
          f"{sum(1 for r in rows if r[2]=='loose')} loose rows", file=sys.stderr)


if __name__ == '__main__':
    main()
