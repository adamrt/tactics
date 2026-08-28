#!/usr/bin/env python3
"""Atomically rename a global (D_*, g_*, etc.) across the whole repo.

- Rewrites every occurrence in src/, wip/, include/ (word-bounded).
- Updates config/linker-symbols.yaml across ALL module blocks.
- Updates config/<mod>-symbols.yaml `name:` entries.
- Uses fcntl locking.

Usage: rename_global.py --old D_800596E0 --new g_player_inventory
"""
import argparse, os, re, sys, fcntl, pathlib

ROOT = pathlib.Path('/Users/adam/src/tactics')

def lock():
    p = ROOT/'config/.promote.lock'
    fh = open(p, 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--old', required=True)
    p.add_argument('--new', required=True)
    args = p.parse_args()
    old, new = args.old, args.new
    if old == new: return

    pat = re.compile(rf'\b{re.escape(old)}\b')

    lk = lock()
    try:
        n_files = 0
        for root_dir in ['src', 'wip', 'include']:
            for f in (ROOT/root_dir).rglob('*'):
                if not f.is_file(): continue
                if f.suffix not in ('.c','.h','.ld'): continue
                text = f.read_text()
                if old not in text: continue
                new_text = pat.sub(new, text)
                if new_text != text:
                    f.write_text(new_text)
                    n_files += 1

        lp = ROOT/'config/linker-symbols.yaml'
        lines = lp.read_text().splitlines(keepends=True)
        # Walk block by block. A blind regex rename produced duplicate keys
        # whenever NEW was already bound in the same block (merging a D_ alias
        # onto its established name), and yaml.v3 rejects duplicate keys, so
        # two workers had to repair the file by hand. Handle the three cases:
        #   NEW absent in block            -> rename OLD's line in place
        #   NEW present, same address      -> delete OLD's line (alias merge)
        #   NEW present, different address -> refuse; this is a real collision
        bind = re.compile(r'''^(\s+)(\w+)(\s*:\s*)['"]?(0x[0-9a-fA-F]+)['"]?\s*$''')
        block_start = None
        changed = False
        i = 0
        while i <= len(lines):
            at_header = i == len(lines) or re.match(r'\s*-\s*id:\s*\S+', lines[i])
            if at_header:
                if block_start is not None:
                    old_i = new_i = None
                    old_addr = new_addr = None
                    for j in range(block_start, i):
                        m = bind.match(lines[j])
                        if not m: continue
                        if m.group(2) == old: old_i, old_addr = j, int(m.group(4), 16)
                        elif m.group(2) == new: new_i, new_addr = j, int(m.group(4), 16)
                    if old_i is not None:
                        if new_i is None:
                            m = bind.match(lines[old_i])
                            lines[old_i] = f"{m.group(1)}{new}{m.group(3)}'0x{old_addr:08x}'\n"
                            changed = True
                        elif new_addr == old_addr:
                            del lines[old_i]; i -= 1; changed = True
                        else:
                            raise SystemExit(
                                f"refusing: {new} is already bound at 0x{new_addr:08x} in the "
                                f"same linker block where {old} is 0x{old_addr:08x}")
                block_start = i
            i += 1
        if changed:
            lp.write_text(''.join(lines)); n_files += 1

        for sp in ROOT.glob('config/*-symbols.yaml'):
            if sp.name == 'linker-symbols.yaml': continue
            st = sp.read_text()
            nst = re.sub(rf'\bname:\s*{re.escape(old)}\s*,', f'name: {new},', st)
            if nst != st:
                sp.write_text(nst); n_files += 1

        print(f"renamed global {old} -> {new} across {n_files} files")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN)
        lk.close()

if __name__ == '__main__':
    main()
