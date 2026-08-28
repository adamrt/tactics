#!/usr/bin/env python3
"""Report reconstruction coverage per module, as a percentage of *code* bytes.

The denominator is deliberately not the module's file size: BATTLE.BIN is 1.4 MB
but most of that is data, so dividing by it would understate progress by an order
of magnitude and make the goal unreadable. Instead the denominator is the union
of the routine address ranges listed on that module's FFHacktics "Routines" wiki
page -- i.e. the bytes the wiki believes are executable code.

That denominator is a lower bound on real code: routines the wiki never catalogued
are invisible to it, so a module can in principle exceed 100%. Treat these numbers
as progress against the *known* code map, not against ground truth.

Usage:
    python3 scripts/coverage.py            # all modules with a routine map
    python3 scripts/coverage.py --goal 25  # flag modules under a threshold
"""
import argparse, re, os, sys

# Modules whose code extent we can measure, and the wiki page listing routines.
# main is spread across several sections of the SCUS routine dump rather than a
# single overlay page, so it is handled separately.
ROUTINE_PAGES = {
    'battle':          'original/ffhacktics/wiki/pages/00000161.wiki',
    'world':           'original/ffhacktics/wiki/pages/00000836.wiki',
    'wldcore':         'original/ffhacktics/wiki/pages/00000837.wiki',
    'opening':         'original/ffhacktics/wiki/pages/00007311.wiki',
    'event-attack':    'original/ffhacktics/wiki/pages/00009425.wiki',
    'event-etc':       'original/ffhacktics/wiki/pages/00009424.wiki',
    'event-helpmenu':  'original/ffhacktics/wiki/pages/00010918.wiki',
    'event-bunit':     'original/ffhacktics/wiki/pages/00009927.wiki',
    'event-card':      'original/ffhacktics/wiki/pages/00010822.wiki',
    'event-debugchr':  'original/ffhacktics/wiki/pages/00010925.wiki',
    'event-equip':     'original/ffhacktics/wiki/pages/00002339.wiki',
    'event-jobstts':   'original/ffhacktics/wiki/pages/00010007.wiki',
    'event-option':    'original/ffhacktics/wiki/pages/00010803.wiki',
    'event-require':   'original/ffhacktics/wiki/pages/00009423.wiki',
}
MAIN_DUMP = 'original/ffhacktics/scus_94221_routines.wiki.txt'

RANGE_RE = re.compile(
    r'^\s*\[?\[?([0-9a-fA-F]{6,8})\s*-\s*([0-9a-fA-F]{6,8})\]?\]?:')


def code_bytes(path):
    """Union of routine ranges on a wiki listing page, in bytes.

    Ranges are unioned rather than summed because the pages occasionally list a
    routine twice (once under a descriptive name, once under its address) and a
    naive sum would double-count it.
    """
    if not os.path.exists(path):
        return 0
    spans = []
    for line in open(path, errors='replace'):
        m = RANGE_RE.match(line)
        if not m:
            continue
        a = int(m.group(1), 16) | 0x80000000
        e = int(m.group(2), 16) | 0x80000000
        if e < a or e - a > 0x20000:      # malformed row; skip rather than skew
            continue
        spans.append((a, e + 4))
    spans.sort()
    total = 0
    cur_a = cur_e = None
    for a, e in spans:
        if cur_e is None or a > cur_e:
            if cur_e is not None:
                total += cur_e - cur_a
            cur_a, cur_e = a, e
        else:
            cur_e = max(cur_e, e)
    if cur_e is not None:
        total += cur_e - cur_a
    return total


def reconstructed():
    """{module_id: (bytes, count)} from modules.yaml.

    Entries appear in two shapes: most are flow-style one-liners, but some were
    written block-style (`- symbol: x` followed by indented keys). Both are valid
    YAML and both are in the file, so parse them the same way rather than only
    counting the one-liners -- doing that silently undercounts coverage.
    """
    out = {}
    mid = None
    pend_bytes = None
    pend_matching = False

    def flush():
        nonlocal pend_bytes, pend_matching
        if mid and pend_matching and pend_bytes is not None:
            got, n = out.get(mid, (0, 0))
            out[mid] = (got + pend_bytes, n + 1)
        pend_bytes, pend_matching = None, False

    for line in open('config/modules.yaml'):
        m = re.match(r'\s*-\s+id:\s*(\S+)', line)
        if m:
            flush()
            mid = m.group(1)
            continue
        if re.match(r'\s*-\s', line):     # a new list entry starts here
            flush()
        if not mid:
            continue
        if 'status: matching' in line:
            pend_matching = True
        b = re.search(r'\bbytes:\s*(\d+)', line)
        if b:
            pend_bytes = int(b.group(1))
        if line.strip().startswith('- {'):   # flow-style: complete on this line
            flush()
    flush()
    return out


def main():
    p = argparse.ArgumentParser()
    p.add_argument('--goal', type=float, default=None,
                   help='threshold %% to flag modules against')
    args = p.parse_args()

    recon = reconstructed()
    pages = dict(ROUTINE_PAGES)
    pages['main'] = MAIN_DUMP

    rows = []
    for mid, page in pages.items():
        total = code_bytes(page)
        if not total:
            continue
        got, n = recon.get(mid, (0, 0))
        rows.append((100.0 * got / total, mid, got, total, n))
    rows.sort()

    print(f"{'module':<18}{'done':>10}{'code':>10}{'pct':>8}{'funcs':>8}")
    print('-' * 54)
    agg_got = agg_total = agg_n = 0
    for pct, mid, got, total, n in rows:
        flag = ''
        if args.goal is not None:
            flag = '  ' if pct >= args.goal else '  <'
        print(f"{mid:<18}{got:>10}{total:>10}{pct:>7.1f}%{n:>8}{flag}")
        agg_got += got
        agg_total += total
        agg_n += n
    print('-' * 54)
    agg = 100.0 * agg_got / agg_total if agg_total else 0.0
    print(f"{'AGGREGATE':<18}{agg_got:>10}{agg_total:>10}{agg:>7.1f}%{agg_n:>8}")

    if args.goal is not None:
        short = [r[1] for r in rows if r[0] < args.goal]
        if short:
            print(f"\nunder {args.goal:g}%: {', '.join(short)}")


if __name__ == '__main__':
    main()
