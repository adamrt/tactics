#!/usr/bin/env python3
"""Promote a matching WIP draft to src/ with full config updates.

Concurrency-safe: takes an exclusive fcntl lock on config/.promote.lock while
mutating any config/*.yaml file, so parallel worker invocations serialize.

Usage:
  promote_wip.py --module <mid> --symbol <sym> --address 0x... --end 0x... \
      --wip-c wip/<mod>/<sym>.c --wip-ld wip/<mod>/<sym>.ld
"""
import argparse, os, re, sys, fcntl, shutil, pathlib, time

ROOT = pathlib.Path('/Users/adam/src/tactics')

# Module id -> src subdir + reviewed-symbols yaml filename
MODULE_MAP = {
    'battle':          ('battle',   'battle-symbols.yaml'),
    'main':            ('main',     'main-symbols.yaml'),
    'opening':         ('open',     'opening-symbols.yaml'),
    'world':           ('world',    'world-symbols.yaml'),
    'wldcore':         ('wldcore',  'wldcore-symbols.yaml'),
    'event-bunit':     ('event',    'bunit-symbols.yaml'),
    'event-card':      ('event',    'card-symbols.yaml'),
    'event-etc':       ('event',    'etc-symbols.yaml'),
    'event-option':    ('event',    'option-symbols.yaml'),
    'event-attack':    ('event',    'attack-symbols.yaml'),
    'event-jobstts':   ('event',    'jobstts-symbols.yaml'),
    'event-equip':     ('event',    'equip-symbols.yaml'),
    'event-require':   ('event',    'require-symbols.yaml'),
    'event-debugchr':  ('event',    'debugchr-symbols.yaml'),
    'event-helpmenu':  ('event',    'helpmenu-symbols.yaml'),
    'event-small':     ('event',    'small-symbols.yaml'),
    'event-attack':    ('event',    'attack-symbols.yaml'),
    'effect-e015':     ('effect',   'effect-e015-symbols.yaml'),
    'effect-e047':     ('effect',   'effect-e047-symbols.yaml'),
    'effect-e259':     ('effect',   'effect-e259-symbols.yaml'),
}

def lock():
    p = ROOT/'config/.promote.lock'
    fh = open(p, 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh

def module_meta(mid):
    with open(ROOT/'config/modules.yaml') as f:
        cur=None; la=None; cls=None
        for line in f:
            m=re.match(r'\s*-\s*id:\s*(\S+)', line)
            if m: cur=m.group(1)
            if cur==mid:
                mm=re.search(r'load_address:\s*"?(0x[0-9a-fA-F]+)"?', line)
                if mm and la is None: la=int(mm.group(1),16)
                mm=re.search(r'classification:\s*(\S+)', line)
                if mm and cls is None: cls=mm.group(1).strip('"')
                if la is not None and cls is not None: break
    if la is None: raise SystemExit(f"module {mid} not found")
    return la, cls

def rodata_range(ld_path):
    """(address, bytes) of a .rodata placement in a wip linker script, or None.

    A function with a GCC jump table needs its .rodata pinned to the target
    address. The build only emits that placement when the reconstruction record
    carries a verified_ranges entry (see generateLinkerScript in
    cmd/tools/linker.go), so a promotion that drops it produces a link whose
    jump-table base points somewhere else -- silently, until the next full build.
    """
    if not os.path.exists(ld_path):
        return None
    text = open(ld_path).read()
    m = re.search(r'\.rodata\s+(0x[0-9a-fA-F]+)', text)
    if not m:
        return None
    return int(m.group(1), 16)


def insert_reconstruction(mid, symbol, addr, end, src_rel, profile=None,
                          rodata_addr=None, rodata_bytes=None):
    la, cls = module_meta(mid)
    bias = 0x800 if cls=='ps-x-exe' else 0
    off_start = addr - la + bias
    off_end   = end - la + bias - 1
    nbytes    = end - addr
    # Only spell out the profile when it is not the project default; the build
    # falls back to the canonical one when the field is absent.
    prof = f', canonical_profile: {profile}' if profile and profile != 'gcc-2.6.3_O2_aspsx-2.34' else ''
    extra = ''
    if rodata_addr is not None and rodata_bytes:
        r_start = rodata_addr - la + bias
        r_end = r_start + rodata_bytes - 1
        extra = (f', verified_ranges: [{{ section: .rodata, '
                 f'address: "0x{rodata_addr:08x}", '
                 f'file_range: "0x{r_start:x}-0x{r_end:x}", '
                 f'bytes: {rodata_bytes} }}]')
    entry = (f'      - {{ symbol: {symbol}, address: "0x{addr:08x}", '
             f'file_range: "0x{off_start:x}-0x{off_end:x}", bytes: {nbytes}, '
             f'language: c, status: matching, source: {src_rel}{prof}{extra} }}\n')
    path = ROOT/'config/modules.yaml'
    text = path.read_text()
    # Idempotency, keyed on (symbol, address). Wiki titles are not unique --
    # distinct functions share one, e.g. "Prep for Initialize Deployed Units'
    # Data" at both 0x8017f5f8 and 0x8017f620. Matching on the name alone made
    # the second promotion a silent no-op that still wrote a linker-symbols
    # entry pointing at the wrong address, so refuse it loudly instead.
    existing = re.search(rf'symbol:\s*{re.escape(symbol)}\s*,\s*address:\s*"(0x[0-9a-fA-F]+)"', text)
    if existing:
        if int(existing.group(1), 16) == addr:
            return 'exists'
        raise SystemExit(
            f"symbol {symbol} is already reconstructed at {existing.group(1)}, "
            f"but this promotion is for 0x{addr:08x}. Two different functions "
            f"share a wiki title -- give this one a distinct name (e.g. append "
            f"the address) and retry.")
    lines = text.splitlines(keepends=True)
    # Find module block start
    mod_i=None
    for i,l in enumerate(lines):
        if re.match(rf'\s*-\s*id:\s*{re.escape(mid)}\s*$', l):
            mod_i=i; break
    if mod_i is None: raise SystemExit(f"module {mid} block not found")
    # Find reconstructions: line
    recon_i=None
    end_i=len(lines)
    for i in range(mod_i, len(lines)):
        if i!=mod_i and re.match(r'\s*-\s*id:', lines[i]):
            end_i=i; break
        if re.match(r'\s*reconstructions:\s*$', lines[i]):
            recon_i=i+1
    if recon_i is None: raise SystemExit(f"reconstructions: not found for {mid}")
    # Scan the reconstructions block. Each list item may be a flow one-liner
    # (starts with "      - { ...") or a block-style entry (starts with "      - symbol: ..."
    # followed by continuation lines at 8-space indent).
    # We only want to insert AFTER a completed entry, never inside a block-style entry.
    # Iterate: find each item's start line, and for block-style, skip its continuation.
    item_lines = []  # list of (line_index, address_int)
    i = recon_i
    while i < end_i:
        line = lines[i]
        if not line.startswith('      - '):
            # End of reconstructions block content
            if line.strip()=='' or line.startswith('  '):  # blank or module-level indented key
                if line.startswith('  -') and not line.startswith('    '): break
                # allow blank lines or trailing content
                if line.strip()=='':
                    i+=1; continue
                if line.startswith('      '):
                    i+=1; continue
                break
            break
        # This is a list-item start.
        m = re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
        if m:
            addr_int = int(m.group(1),16)
        else:
            addr_int = None
        # Walk forward past continuation lines (8-space indent, no leading "-")
        j = i+1
        while j<end_i:
            ln = lines[j]
            if ln.startswith('      - ') or (not ln.startswith('        ') and ln.strip()!=''):
                break
            j+=1
        item_lines.append((i, addr_int, j))  # (start, addr, end_exclusive)
        i = j
    # Find insertion point: first item with addr > our addr; else after last item
    insert_at = None
    for start, aint, jend in item_lines:
        if aint is not None and aint > addr:
            insert_at = start
            break
    if insert_at is None:
        insert_at = item_lines[-1][2] if item_lines else recon_i
    lines.insert(insert_at, entry)
    path.write_text(''.join(lines))
    return 'inserted'

def insert_reviewed_symbol(mid, symbol, addr, end):
    if mid not in MODULE_MAP: return 'no-map'
    subdir, sym_file = MODULE_MAP[mid]
    path = ROOT/'config'/sym_file
    if not path.exists(): return 'no-file'
    text = path.read_text()
    if re.search(rf'name:\s*{re.escape(symbol)}[\s,]', text):
        return 'exists'
    lines = text.splitlines(keepends=True)
    entry = (f'  - {{ name: {symbol}, address: "0x{addr:08x}", '
             f'end: "0x{end:08x}", kind: function, ownership: game, confidence: high }}\n')
    # Find address-ordered insertion point within the file's symbol list.
    # Each symbol line: `  - { name: X, address: "0x...", ... }`
    insert_at = None
    for i, l in enumerate(lines):
        m = re.search(r'address:\s*"(0x[0-9a-fA-F]+)".*kind:\s*function', l)
        if m and int(m.group(1),16) > addr:
            insert_at = i
            break
    if insert_at is None:
        # Append at end (before trailing blank lines)
        insert_at = len(lines)
        while insert_at>0 and lines[insert_at-1].strip()=='':
            insert_at -= 1
    lines.insert(insert_at, entry)
    path.write_text(''.join(lines))
    return 'inserted'

def merge_linker_externs(mid, ld_path):
    if not os.path.exists(ld_path): return 0
    externs={}
    for line in open(ld_path):
        m = re.match(r'\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9a-fA-F]+)\s*;', line)
        if m: externs[m.group(1)] = m.group(2).lower()
    if not externs: return 0
    path = ROOT/'config/linker-symbols.yaml'
    lines = path.read_text().splitlines(keepends=True)
    start=end=None
    for i,l in enumerate(lines):
        if re.match(rf'-\s*id:\s*{re.escape(mid)}\s*$', l):
            start=i; break
    if start is None: return 0
    for i in range(start+1, len(lines)):
        if re.match(r'-\s*id:', lines[i]):
            end=i; break
    if end is None: end=len(lines)
    existing=set()
    for l in lines[start:end]:
        m = re.match(r'\s*([A-Za-z_][A-Za-z0-9_]*):\s*[\'"]?(0x[0-9a-fA-F]+)', l)
        if m: existing.add(m.group(1))
    to_add = [f"    {name}: '{addr}'\n" for name,addr in externs.items() if name not in existing]
    if not to_add: return 0
    # Insert at the end of the module's `symbols:` map. A module block may end
    # with an `overrides:` sub-map whose entries are nested one level deeper;
    # appending past it would land inside that map and break the schema.
    ins = end
    for i in range(start, end):
        if re.match(r'\s*overrides:\s*$', lines[i]):
            ins = i
            break
    while ins > start and lines[ins-1].strip() == '':
        ins -= 1
    lines[ins:ins] = to_add
    path.write_text(''.join(lines))
    return len(to_add)

def remove_wip_entry(symbol):
    path = ROOT/'config/wip.yaml'
    lines = path.read_text().splitlines(keepends=True)
    kept = [l for l in lines if f'symbol: {symbol},' not in l]
    if len(kept)!=len(lines):
        path.write_text(''.join(kept)); return True
    return False

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--module', required=True)
    p.add_argument('--symbol', required=True)
    p.add_argument('--address', required=True)
    p.add_argument('--end', required=True)
    p.add_argument('--wip-c', required=True)
    p.add_argument('--wip-ld', required=True)
    p.add_argument('--profile', default=None,
                   help='non-default compiler profile, e.g. gcc-2.6.3_O2_aspsx-2.21')
    p.add_argument('--rodata-bytes', type=int, default=None,
                   help='size of the function\'s .rodata (jump table). The '
                        'address is read from the wip .ld; without this the '
                        'promoted record cannot pin the jump table and the '
                        'next full build will mismatch.')
    args=p.parse_args()

    if args.module not in MODULE_MAP:
        raise SystemExit(f"module {args.module} not in MODULE_MAP (add it to scripts/promote_wip.py)")
    subdir,_ = MODULE_MAP[args.module]
    addr = int(args.address,16)
    end = int(args.end,16)
    wip_c = ROOT/args.wip_c
    wip_ld = ROOT/args.wip_ld
    if not wip_c.exists(): raise SystemExit(f"wip C not found: {wip_c}")

    src_dir = ROOT/'src'/subdir
    src_dir.mkdir(exist_ok=True)
    src_c = src_dir/wip_c.name
    src_rel = f"src/{subdir}/{wip_c.name}"

    lk = lock()
    try:
        rod = rodata_range(str(wip_ld))
        if rod is not None and not args.rodata_bytes:
            raise SystemExit(
                f"{wip_ld} pins .rodata at 0x{rod:08x} (a jump table), but "
                f"--rodata-bytes was not given. Promoting without it drops the "
                f"placement from modules.yaml, so the build would link the jump "
                f"table at the wrong address. Pass the table's size in bytes.")
        n_ext = merge_linker_externs(args.module, str(wip_ld))
        r_rev = insert_reviewed_symbol(args.module, args.symbol, addr, end)
        r_rec = insert_reconstruction(args.module, args.symbol, addr, end, src_rel,
                                      args.profile, rod, args.rodata_bytes)
        # Move file & remove ld
        if not src_c.exists():
            shutil.move(str(wip_c), str(src_c))
        else:
            # Src already exists — likely duplicate promotion. Clean up wip.
            wip_c.unlink(missing_ok=True)
        if wip_ld.exists(): wip_ld.unlink()
        removed = remove_wip_entry(args.symbol)
        print(f"promoted {args.symbol}: rec={r_rec} rev={r_rev} externs+{n_ext} wip_removed={removed} → {src_rel}")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN)
        lk.close()

if __name__=='__main__': main()
