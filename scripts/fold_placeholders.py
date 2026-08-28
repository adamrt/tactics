#!/usr/bin/env python3
"""Fold stale `func_XXXXXXXX` extern references onto the real symbol name.

A reconstruction that was drafted before its callee had a name declares the
callee as `func_<address>`. Once the callee is promoted under a real name, those
references are stale: they still link (same address) but the code reads as if
the callee were unknown, and `grep` for the real name misses every caller.

This folds them. For each (placeholder, real) pair it:
  * confirms the placeholder's hex address equals the real symbol's bound
    address in that module's linker-symbols block (refusing otherwise -- a
    same-base overlay collision would look identical by name alone);
  * rewrites `\\bplaceholder\\b` -> real in the given src/ files;
  * reconciles config/linker-symbols.yaml so the real name is bound in every
    module block that previously bound the placeholder, and drops the
    placeholder binding.

It is deliberately NOT scripts/rename_symbol.py: that renames a *defined*
function (moves the .c, edits modules.yaml). Here the definition already has the
right name; only references move. No bytes change -- an extern's name is not in
the object -- but linkage does, so run the module build afterwards.

Usage:
  fold_placeholders.py --pairs pairs.tsv [--exclude files.txt] [--apply]
pairs.tsv rows: placeholder<TAB>real<TAB>module_id
"""
import argparse, re, glob, fcntl, pathlib, sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
LINKER = ROOT / 'config/linker-symbols.yaml'


def lock():
    fh = open(ROOT / 'config/.promote.lock', 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh


def linker_blocks(text):
    """[(module_id, start_line, end_line)] over linker-symbols.yaml lines."""
    lines = text.splitlines(keepends=True)
    blocks = []
    cur = None
    for i, line in enumerate(lines):
        m = re.match(r'\s*-\s*id:\s*(\S+)', line)
        if m:
            if cur:
                blocks.append((cur[0], cur[1], i))
            cur = (m.group(1), i)
    if cur:
        blocks.append((cur[0], cur[1], len(lines)))
    return lines, blocks


def bound_address(lines, start, end, name):
    # Bindings appear with either quote style: the promote script writes
    # single quotes, older hand edits used double.
    pat = re.compile(r'(\s*)' + re.escape(name) + r''':\s*['"](0x[0-9a-fA-F]+)['"]''')
    for i in range(start, end):
        m = pat.match(lines[i])
        if m:
            return int(m.group(2), 16), i, m.group(1)
    return None, None, None


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--pairs', required=True)
    ap.add_argument('--exclude', help='file of src paths to leave untouched')
    ap.add_argument('--apply', action='store_true')
    args = ap.parse_args()

    exclude = set()
    if args.exclude:
        exclude = {l.strip() for l in open(args.exclude) if l.strip()}

    pairs = []
    for line in open(args.pairs):
        p = line.rstrip('\n').split('\t')
        if len(p) >= 3 and re.match(r'func_[0-9A-Fa-f]{8}$', p[0]):
            pairs.append((p[0], p[1], p[2]))

    lk = lock()
    try:
        ltext = LINKER.read_text()
        lines, blocks = linker_blocks(ltext)
        srcs = {p: open(p).read() for p in glob.glob(str(ROOT / 'src/*/*.c'))}

        touched_src = {}
        refused = []
        rebind = []   # (line_index, new_line) / deletions
        for ph, real, mid in pairs:
            ph_addr = int(ph[5:], 16)
            edited_here = 0
            for path, text in srcs.items():
                rel = str(pathlib.Path(path).relative_to(ROOT))
                if rel in exclude:
                    continue
                if re.search(r'\b' + ph + r'\b', text):
                    new = re.sub(r'\b' + ph + r'\b', real, text)
                    srcs[path] = new
                    touched_src[path] = new
                    edited_here += 1
            # Reconcile every linker block that binds the placeholder.
            for bmid, s, e in blocks:
                a, li, indent = bound_address(lines, s, e, ph)
                if a is None:
                    continue
                if a != ph_addr:
                    refused.append((ph, real, bmid, f'placeholder bound at 0x{a:08x} != name 0x{ph_addr:08x}'))
                    continue
                ra, rli, _ = bound_address(lines, s, e, real)
                if ra is None:
                    # rename the binding in place: real takes the placeholder's line
                    rebind.append((li, f"{indent}{real}: '0x{a:08x}'\n"))
                elif ra != a:
                    refused.append((ph, real, bmid, f'real already bound at 0x{ra:08x}, placeholder at 0x{a:08x}'))
                else:
                    rebind.append((li, None))   # both present, same address: drop placeholder
            print(f"{'APPLY' if args.apply else 'plan '}: {ph} -> {real}  ({edited_here} files, module {mid})")

        for ph, real, bmid, why in refused:
            print(f"REFUSED: {ph} -> {real} in {bmid}: {why}", file=sys.stderr)

        if not args.apply:
            print(f"\ndry run: {len(touched_src)} src files, {len(rebind)} linker edits, {len(refused)} refused")
            return

        # Apply linker edits from the bottom up so indices stay valid.
        for li, new in sorted(rebind, key=lambda r: -r[0]):
            if new is None:
                del lines[li]
            else:
                lines[li] = new
        LINKER.write_text(''.join(lines))
        for path, text in touched_src.items():
            open(path, 'w').write(text)
        print(f"\napplied: {len(touched_src)} src files rewritten, {len(rebind)} linker edits, {len(refused)} refused")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN); lk.close()


if __name__ == '__main__':
    main()
