#!/usr/bin/env python3
"""Regenerate /tmp/batch_N.tsv files from fresh modules.yaml/wip.yaml state.

Reads:
- /tmp/candidates.txt (the full pool: `module<TAB>size<TAB>addr<TAB>end<TAB>name`)
- config/modules.yaml (currently-reconstructed addresses)
- config/wip.yaml (currently-tracked WIP addresses)
- config/skip-addresses.txt (never-reconstructable entries, with reasons)
- config/.batch-claims.tsv (addresses handed to a still-running worker)

Claims exist because a worker only registers its draft in wip.yaml once it has
something compiling, which can be an hour in. Until then the address looks free,
so a later batch hands the same function to a second worker and one of them
loses the race — `promote_wip.py` deletes the wip file underneath the other.
Generating a batch claims its rows; release them with --release when the worker
reports back.

Writes:
- /tmp/batch_<N>.tsv (starting from --start-batch, up to --num-batches batches
  of --batch-size)
- /tmp/batches_summary.txt with row counts

Symbols are normalized from wiki names to snake_case; module prefix added when
sensible to reduce collisions.
"""
import argparse, re, os, fcntl, time

CLAIMS = 'config/.batch-claims.tsv'


def _lock():
    fh = open('config/.promote.lock', 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh


def read_claims():
    """Return {"module|address": batch}. Missing file means nothing is claimed.

    Keyed by module as well as address because several event overlays share a
    load address; a bare address key would let one overlay's claim block work on
    a different overlay entirely.
    """
    claims = {}
    if not os.path.exists(CLAIMS):
        return claims
    for line in open(CLAIMS):
        if line.startswith('#'):
            continue
        parts = line.rstrip('\n').split('\t')
        if len(parts) >= 2:
            claims[parts[0].lower()] = parts[1]
    return claims


def write_claims(claims):
    with open(CLAIMS, 'w') as f:
        f.write('# module|address\tbatch\tclaimed_at'
                ' -- see scripts/regen_batches.py\n')
        for key, batch in sorted(claims.items()):
            f.write(f"{key}\t{batch}\t{time.strftime('%Y-%m-%dT%H:%M:%S')}\n")


def release(batches):
    """Drop claims for the named batches so their rows can be re-issued."""
    lk = _lock()
    try:
        claims = read_claims()
        want = {str(b) for b in batches}
        kept = {a: b for a, b in claims.items() if b not in want}
        write_claims(kept)
        print(f"release: dropped {len(claims) - len(kept)} claims for "
              f"batch(es) {','.join(sorted(want))}; {len(kept)} still claimed")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN); lk.close()

def normalize(name):
    n = re.sub(r'\s*\([^)]*\)\s*', ' ', name)
    n = re.sub(r'[^A-Za-z0-9_]+', '_', n)
    n = re.sub(r'_+', '_', n).strip('_').lower()
    return n[:60]

def main():
    p=argparse.ArgumentParser()
    p.add_argument('--start-batch', type=int, default=1)
    p.add_argument('--num-batches', type=int, default=30)
    p.add_argument('--batch-size', type=int, default=10)
    p.add_argument('--max-size', type=int, default=200)
    p.add_argument('--pool', default='/tmp/candidates.txt')
    p.add_argument('--release', metavar='N', nargs='+',
                   help='release claims held by these batch numbers and exit')
    p.add_argument('--no-claim', action='store_true',
                   help='generate without claiming (for inspection only)')
    args=p.parse_args()

    if args.release:
        release(args.release)
        return

    lk = _lock()

    # Keyed by (module, address). Several event overlays load at the same base
    # (OPTION/REQUIRE/ATTACK/BUNIT all at 0x801bf000), so a bare address set
    # makes one overlay's reconstruction mask every other overlay's function at
    # the same offset and silently empties those modules' candidate pools.
    recon=set()
    mid_cur=None
    for line in open('config/modules.yaml'):
        mm=re.match(r'\s*-\s+id:\s*(\S+)', line)
        if mm:
            mid_cur=mm.group(1); continue
        m=re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
        if m and mid_cur: recon.add((mid_cur, m.group(1).lower()))
    wip=set()
    for line in open('config/wip.yaml'):
        m=re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
        mm=re.search(r'module:\s*([\w-]+)', line)
        if m: wip.add((mm.group(1) if mm else None, m.group(1).lower()))
    skip=set()
    if os.path.exists('config/skip-addresses.txt'):
        for line in open('config/skip-addresses.txt'):
            m=re.match(r'\s*(0x[0-9a-fA-F]+)', line)
            if m: skip.add(m.group(1).lower())
    claims = read_claims()

    cands=[]
    for line in open(args.pool):
        parts=line.rstrip('\n').split('\t')
        if len(parts)!=5: continue
        mid,sz,addr,end,name=parts
        sz=int(sz)
        if sz>args.max_size: continue
        addr=addr.lower(); end=end.lower()
        if (mid, addr) in recon or (mid, addr) in wip: continue
        if addr in skip: continue
        if f"{mid}|{addr}" in claims: continue
        if not name: continue
        sym=normalize(name)
        if not sym or sym[0].isdigit(): continue
        if mid.startswith('event-'):
            prefix=mid.split('-')[1]+'_'
            if not sym.startswith(prefix): sym=prefix+sym
        elif mid=='battle' and not sym.startswith('battle_') and len(sym)<20:
            sym='battle_'+sym
        elif mid=='world' and not sym.startswith('world_') and len(sym)<20:
            sym='world_'+sym
        cands.append((sz,mid,addr,end,sym,name))
    cands.sort()

    written=0
    try:
        for i in range(args.num_batches):
            b=cands[i*args.batch_size:(i+1)*args.batch_size]
            if not b: break
            n=args.start_batch+i
            with open(f'/tmp/batch_{n}.tsv','w') as f:
                for sz,mid,addr,end,sym,name in b:
                    f.write(f"{mid}\t{sym}\t{addr}\t{end}\t{sz}\t{name}\n")
                    if not args.no_claim: claims[f"{mid}|{addr}"]=str(n)
            written+=1
        if not args.no_claim: write_claims(claims)
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN); lk.close()
    print(f"regen: wrote {written} batches starting at batch_{args.start_batch}")
    print(f"total available candidates now: {len(cands)}"
          f"{'' if args.no_claim else f' ({len(claims)} claimed)'}")

if __name__=='__main__': main()
