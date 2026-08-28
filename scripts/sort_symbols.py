#!/usr/bin/env python3
"""Sort function entries in a *-symbols.yaml file by their address field.

Only touches lines that are recognizable function-entry flow one-liners of the form:
  `  - { name: ..., address: "0x...", ... kind: function, ... }`
All other lines (headers, comments, non-function entries) are left in-place at
their original relative position.

Usage: sort_symbols.py <path/to/*-symbols.yaml> [more paths...]
"""
import sys, re

FN_RE = re.compile(r'^\s*-\s*\{\s*name:\s*[A-Za-z_][\w]*\s*,\s*address:\s*"(0x[0-9a-fA-F]+)".*kind:\s*function\b')

def sort_file(path):
    lines = open(path).readlines()
    fn_idxs = []
    for i, l in enumerate(lines):
        m = FN_RE.match(l)
        if m:
            fn_idxs.append((i, int(m.group(1), 16)))
    if not fn_idxs:
        print(f"{path}: no function entries found"); return
    # Extract the function lines in file order
    ordered_lines = [lines[i] for i,_ in fn_idxs]
    # Sort by address, but preserve the count
    ordered_lines.sort(key=lambda l: int(FN_RE.match(l).group(1), 16))
    # Re-inject into original positions in order
    for (i,_), new_l in zip(fn_idxs, ordered_lines):
        lines[i] = new_l
    open(path, 'w').writelines(lines)
    print(f"{path}: sorted {len(fn_idxs)} function entries")

if __name__=='__main__':
    for p in sys.argv[1:]:
        sort_file(p)
