#!/usr/bin/env python3
"""Atomically rename a src/ function's symbol across all config files.

- Renames the .c file (src/<subdir>/<old>.c → src/<subdir>/<new>.c)
- Renames the function definition inside the .c
- Updates modules.yaml `symbol:` field
- Updates <module>-symbols.yaml `name:` field
- Updates linker-symbols.yaml occurrences of the old symbol across ALL module blocks
  (so callers that reference this symbol continue to link)
- Uses fcntl locking

Usage:
  rename_symbol.py --old <old_symbol> --new <new_symbol>
"""
import argparse, os, re, sys, fcntl, pathlib, shutil

ROOT = pathlib.Path('/Users/adam/src/tactics')

def lock():
    p = ROOT/'config/.promote.lock'
    fh = open(p, 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh

def find_src_file(sym):
    # Usual case: src/<subdir>/<sym>.c
    for c in (ROOT/'src').glob(f'*/{sym}.c'):
        return c
    # Symbol and file name can disagree (e.g. symbol `battle_effect_related`
    # in `battle_effect_related_801a1c90.c`, where the file was disambiguated
    # by address). modules.yaml records the authoritative source path, so fall
    # back to that rather than refusing the rename.
    for line in (ROOT/'config/modules.yaml').read_text().splitlines():
        if re.search(rf'\bsymbol:\s*{re.escape(sym)}\s*[,}}]', line):
            m = re.search(r'source:\s*(src/[^\s,}]+\.c)', line)
            if m:
                return ROOT/m.group(1)
    return None

def main():
    p = argparse.ArgumentParser()
    p.add_argument('--old', required=True)
    p.add_argument('--new', required=True)
    args = p.parse_args()

    old, new = args.old, args.new
    if old == new: return

    src = find_src_file(old)
    if not src:
        raise SystemExit(f"src file for {old} not found")

    lk = lock()
    try:
        # 1. Rename .c file
        new_path = src.parent / f"{new}.c"
        if new_path.exists():
            raise SystemExit(f"target already exists: {new_path}")
        shutil.move(str(src), str(new_path))

        # 2. Replace inside .c — the definition line and any recursive/self reference
        text = new_path.read_text()
        # Word-boundary replace to avoid partial matches
        text = re.sub(rf'\b{re.escape(old)}\b', new, text)
        new_path.write_text(text)

        # 3. modules.yaml: symbol + source
        mp = ROOT/'config/modules.yaml'
        t = mp.read_text()
        # symbol: OLD, ... source: <actual old path>
        # Rewrite the source path by the path we actually moved, not by the
        # symbol name: find_src_file() may have resolved a file whose name does
        # not equal the symbol, and a name-based rewrite would leave
        # modules.yaml pointing at a file that no longer exists.
        old_rel = src.relative_to(ROOT).as_posix()
        new_rel = new_path.relative_to(ROOT).as_posix()
        # Reconstructions use both inline mappings and block mappings.  Match
        # the value token rather than assuming the inline form's comma.
        t = re.sub(
            rf'(\bsymbol:\s*){re.escape(old)}(?=[ \t]*(?:,|$))',
            rf'\1{new}',
            t,
        )
        t = t.replace(f'source: {old_rel}', f'source: {new_rel}')
        mp.write_text(t)

        # 4. <module>-symbols.yaml: replace `name: OLD,` in any *-symbols.yaml
        for sp in ROOT.glob('config/*-symbols.yaml'):
            if sp.name == 'linker-symbols.yaml': continue
            st = sp.read_text()
            nst = re.sub(
                rf'(\bname:\s*){re.escape(old)}(?=[ \t]*(?:,|$))',
                rf'\1{new}',
                st,
            )
            if nst != st:
                sp.write_text(nst)

        # 5. linker-symbols.yaml — rename in every module block
        lp = ROOT/'config/linker-symbols.yaml'
        lt = lp.read_text()
        nlt = re.sub(rf'^(\s+){re.escape(old)}:', rf'\1{new}:', lt, flags=re.MULTILINE)
        if nlt != lt:
            lp.write_text(nlt)

        # 6. Update references in OTHER src files that call this symbol as an extern
        # (only the extern declaration + call site, since the callee is renamed and .ld gets updated)
        for cf in (ROOT/'src').rglob('*.c'):
            if cf == new_path: continue
            ct = cf.read_text()
            if old not in ct: continue
            nct = re.sub(rf'\b{re.escape(old)}\b', new, ct)
            if nct != ct: cf.write_text(nct)

        print(f"renamed {old} -> {new}")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN)
        lk.close()

if __name__ == '__main__':
    main()
