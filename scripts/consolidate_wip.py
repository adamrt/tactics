#!/usr/bin/env python3
"""Reconcile wip/ files with config/wip.yaml. Safe to run alongside workers.

- Registers orphan wip/*.c files (present on disk, missing from wip.yaml).
- Prunes wip.yaml entries whose source file no longer exists.
- Drops entries whose address is already in modules.yaml (promoted).
- De-duplicates (symbol, address) pairs.
- Ensures a trailing newline (the yaml parser needs it).

Uses the same fcntl lock as promote_wip.py.
"""
import os, re, glob, fcntl, pathlib, shutil, time

ROOT = pathlib.Path('/Users/adam/src/tactics')
TRASH = ROOT/'build/wip-trash'

# Leave files this recently modified alone -- a worker is probably mid-iteration
# on them, and retiring a draft out from under a running agent loses real work.
IN_FLIGHT_SECONDS = 30 * 60


def retire(path):
    """Move a wip file aside instead of deleting it.

    Anything reached here is redundant with modules.yaml or unusable, but a
    hard delete has already cost us three drafts, so keep a copy under an
    ignored build/ directory.
    """
    p = pathlib.Path(path)
    if not p.exists():
        return
    dest_dir = TRASH/time.strftime('%Y%m%d')/p.parent.name
    dest_dir.mkdir(parents=True, exist_ok=True)
    dest = dest_dir/p.name
    n = 1
    while dest.exists():
        dest = dest_dir/f"{p.stem}.{n}{p.suffix}"
        n += 1
    shutil.move(str(p), str(dest))

SUBDIR_TO_MODULE = {
    'battle':'battle', 'world':'world', 'wldcore':'wldcore', 'open':'opening',
    'main':'main', 'effect':'effect-e015',
    'card':'event-card', 'option':'event-option', 'require':'event-require',
    'debugchr':'event-debugchr', 'helpmenu':'event-helpmenu',
    'jobstts':'event-jobstts', 'equip':'event-equip', 'attack':'event-attack',
    'event':'event-bunit', 'etc':'event-etc', 'bunit':'event-bunit',
}

def lock():
    fh = open(ROOT/'config/.promote.lock', 'w')
    fcntl.flock(fh, fcntl.LOCK_EX)
    return fh

def ld_text_address(ld_path):
    if not os.path.exists(ld_path): return None
    for line in open(ld_path):
        m = re.search(r'\.text\s+(0x[0-9a-fA-F]+)', line)
        if m: return m.group(1)
    return None

def main():
    lk = lock()
    try:
        wip_path = ROOT/'config/wip.yaml'
        lines = wip_path.read_text().splitlines(keepends=True)

        # Addresses are keyed by (module, address), never by address alone. The
        # event overlays are mutually exclusive and several load at the same
        # base -- OPTION, REQUIRE, ATTACK and BUNIT all start at 0x801bf000 --
        # so a bare address set makes one overlay's function look like every
        # other overlay's function at the same offset, and silently hides real
        # candidates.
        recon_addrs = set()
        mid = None
        for line in (ROOT/'config/modules.yaml').read_text().splitlines():
            mm = re.match(r'\s*-\s+id:\s*(\S+)', line)
            if mm:
                mid = mm.group(1)
                continue
            m = re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
            if m and mid: recon_addrs.add((mid, m.group(1).lower()))

        # Pass 1: prune stale / already-promoted / duplicate entries
        kept, seen, seen_mod = [], set(), set()
        pruned = promoted = dup = 0
        for line in lines:
            ms = re.search(r'source:\s*(wip/\S+\.c)', line)
            ma = re.search(r'(?<![\w])address:\s*"(0x[0-9a-fA-F]+)"', line)
            msym = re.search(r'symbol:\s*(\w+)', line)
            mmid = re.search(r'module:\s*([\w-]+)', line)
            if ms and ma and msym:
                src, addr, sym = ms.group(1), ma.group(1).lower(), msym.group(1)
                wmid = mmid.group(1) if mmid else None
                if not (ROOT/src).exists():
                    pruned += 1; continue
                if (wmid, addr) in recon_addrs:
                    promoted += 1
                    retire(ROOT/src)
                    retire(ROOT/(src[:-2] + '.ld'))
                    continue
                key = (sym, addr)
                if key in seen:
                    dup += 1; continue
                seen.add(key)
                seen_mod.add((wmid, addr))
            kept.append(line)

        registered_syms = {s for s, _ in seen}
        addr_taken = set(recon_addrs) | seen_mod

        # Pass 2: register orphan .c files
        added = 0
        skipped_inflight = 0
        collided = []
        now = time.time()
        for f in sorted(glob.glob(str(ROOT/'wip/*/*.c'))):
            rel = os.path.relpath(f, ROOT)
            sym = os.path.basename(f)[:-2]
            if sym in registered_syms: continue
            # A worker writes the .c before the .ld and iterates on both for a
            # while before anything matches. Retiring a file mid-edit destroys
            # live work -- it has already happened -- so a recently-touched file
            # is never retired. Registering one is harmless (the manifest only
            # tracks drafts; nothing is linked into the disc), and the build
            # rejects any wip/ source missing from the manifest, so in-flight
            # files still get registered when they have a usable .ld.
            try:
                in_flight = now - os.path.getmtime(f) < IN_FLIGHT_SECONDS
            except OSError:
                continue
            subdir = rel.split('/')[1]
            mid = SUBDIR_TO_MODULE.get(subdir, subdir)
            ld = f[:-2] + '.ld'
            addr = ld_text_address(ld)
            if not addr:
                if in_flight:
                    skipped_inflight += 1
                else:
                    retire(f)
                continue
            if (mid, addr.lower()) in addr_taken:
                # Do NOT retire: a collision means either the address is already
                # reconstructed, or a second draft of the same function exists
                # under a different name. Either way the draft may be the better
                # source, so report it and let a human decide which to keep.
                why = ('already reconstructed'
                       if (mid, addr.lower()) in recon_addrs
                       else 'already drafted under another name in wip.yaml')
                collided.append((rel, addr, why))
                continue
            addr_taken.add((mid, addr.lower()))
            registered_syms.add(sym)
            kept.append(
                f"  - {{ module: {mid}, symbol: {sym}, address: \"{addr}\", "
                f"status: wip, source: {rel}, "
                f"canonical_profile: gcc-2.6.3_O2_aspsx-2.34 }}\n")
            added += 1

        text = ''.join(kept)
        if not text.endswith('\n\n'):
            text = text.rstrip('\n') + '\n\n'
        wip_path.write_text(text)
        print(f"consolidate: +{added} registered, -{pruned} stale, "
              f"-{promoted} already-promoted, -{dup} dupes, "
              f"{len(seen) + added} tracked"
              + (f", {skipped_inflight} in-flight (untouched)" if skipped_inflight else ""))
        for rel, addr, why in collided:
            print(f"  COLLISION: {rel} targets {addr}, {why}. "
                  f"Left in place -- resolve by hand.")
    finally:
        fcntl.flock(lk, fcntl.LOCK_UN); lk.close()

if __name__ == '__main__':
    main()
