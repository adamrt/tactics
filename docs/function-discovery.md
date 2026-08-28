# Function discovery

The FFHacktics routine listings are the usual candidate source, but they only
cover part of each overlay. Counting the bytes they name:

| module  | named pool | needed for 25% |
| ------- | ---------- | -------------- |
| world   | ~23 KB     | ~79 KB         |
| wldcore | ~0 KB      | ~51 KB         |
| main    | ~0 KB      | ~55 KB         |

Matching every wiki-named routine in those modules still leaves them far short.
Raising them requires finding functions nobody has catalogued.

`scripts/discover_functions.py` does that by scanning the extracted overlay for
function boundaries:

```sh
python3 scripts/discover_functions.py --module world --validate
python3 scripts/discover_functions.py --module world --emit-pool > pool.txt
python3 scripts/regen_batches.py --pool pool.txt --start-batch 140 --num-batches 4
```

## How boundaries are decided

A function ends at `jr $ra` plus its delay slot, and the next function starts at
the following non-padding word. An address already known to be a function start
forces a boundary, which recovers the cases where GCC emitted a genuine early
return rather than merging returns into one epilogue.

## What was tried and rejected

Treating a `jr $ra` as a boundary only when a `jal` demonstrably targets the
code that follows sounds stricter and is measurably worse. It merges every
function reached only indirectly or by tail call; on BATTLE.BIN it produced a
single 342,668-byte "function", and size disagreements against known
reconstructions rose from 1 to 48. The simple rule wins because GCC 2.6.3
almost always emits a single epilogue.

## Why the output is trustworthy

`--validate` replays the detector against every reconstruction already recorded
in `modules.yaml`. Each known address must be rediscovered at exactly its known
size:

| module  | rediscovered | size disagreements |
| ------- | ------------ | ------------------ |
| world   | 161/161      | 0                  |
| wldcore | 60/60        | 0                  |
| battle  | 1015/1015    | 2                  |
| main    | 37/37        | 1                  |

1273/1273 known functions rediscovered, three size disagreements. Re-run
`--validate` after any change to the detector, and before trusting a new pool.

## Two filters that matter as much as the boundary rule

**Library ownership.** AGENTS.md excludes Sony library and middleware code, and
`config/libraries.yaml` already records those ranges. The detector cross-checks
them, plus addresses already bound in `config/linker-symbols.yaml` (a discovered
range that is already a known extern like `GetGraphType` is code we link
against, not code to reconstruct). This removes 334 of 678 raw `main`
candidates. Before the filter existed, one discovered batch was 75% LIBCD and
LIBGPU getters that a worker had to identify and reject by hand.

**Code extent.** Candidates are bounded to the module's executable region, taken
from its routine-listing page and widened to cover everything already
reconstructed. An overlay file is mostly data, and the word `0x03e00008` occurs
in graphics and tables often enough to manufacture plausible-looking functions
by the hundred: unbounded, EVENT/HELPMENU.OUT reports 99,576 bytes of candidates
against a 5,592-byte code region. Bounded, it reports 5,452.

Any module absent from `ROUTINE_PAGES` falls back to the span of its known
reconstructions, which is conservative but can be narrow. Add the page rather
than widening the bound by guesswork.

## Candidate supply, after filtering

| module         | needs for 25% | discovered |
| -------------- | ------------- | ---------- |
| event-helpmenu | 1.3 KB        | 5.5 KB     |
| event-option   | 1.9 KB        | 15 KB      |
| event-attack   | 5.1 KB        | 39 KB      |
| wldcore        | 51 KB         | 219 KB     |
| main           | 55 KB         | 241 KB     |
| world          | 78 KB         | 354 KB     |
| battle         | 94 KB         | 521 KB     |

Every module short of 25% has more discovered material than it needs. The
constraint on reaching 25% is throughput and match difficulty, not candidate
supply -- which is the opposite of the situation with the wiki-named pool alone.

## Working a discovered candidate

Discovered rows carry a placeholder symbol `func_<address>`. That name is not
evidence of anything. A worker must name the function from its behaviour,
cross-referenced against the wiki and against callers and callees in `src/`, and
keep `func_<address>` when the behaviour is genuinely unclear — a wrong semantic
name is worse than a provisional one.

The detector is reliable, not infallible. A range with no prologue, that reads
registers it never writes, or that ends in a bare `j`, is a mid-function
fragment rather than a function; record it in `config/skip-addresses.txt` with a
reason instead of forcing a reconstruction. The same applies to padding, data
tables, and Sony library code, which AGENTS.md excludes.

## Finding twins

WORLD.BIN and BATTLE.BIN share a large body of menu/event code, and the
EVENT/*.OUT overlays are built from the same sources at different link
addresses. A function that is still `func_<addr>` in one module is often
already named from its behaviour in another. `scripts/find_twins.py` finds
those pairs by computing a masked signature for every `status: matching`
reconstruction and grouping equal signatures:

```sh
python3 scripts/find_twins.py --all-event battle world wldcore --agree
python3 scripts/find_twins.py world event-equip           # any set of module ids
```

Output is a TSV: `placeholder  candidate_name  strict|loose  twin_symbol
twin_module`, one row per (placeholder, real-named twin), with the candidate
already re-prefixed for the placeholder's module.

Two evidence tiers:

- **strict** masks only what the linker relocates: `j`/`jal` targets and the
  16-bit immediates of `lui`/`addiu`/`ori` and of every load/store. Equal
  strict signatures mean the same instruction stream at different addresses
  -- same control flow, same register allocation, same branch offsets, same
  comparison constants. This is strong evidence of identity.
- **loose** additionally masks every 16-bit immediate (branch offsets,
  `slti`/`andi`/`xori`/`addi` constants). Equal loose signatures mean the same
  *shape*, possibly with different constants or table sizes. That is also
  what two unrelated accessors of the same form look like, so a loose match
  must be confirmed by reading both bodies before a name is copied. If the
  constants differ and change the meaning (a different struct size in a
  `memset`, a different flag bit), do not rename.

Two caveats even for strict matches. First, tiny functions are degenerate:
a `jal X; nop; jr ra` wrapper or a store-to-global setter strict-matches
every other wrapper/setter because the only distinguishing field was masked.
Such a group proves the placeholder *is* a wrapper, not which one; `--agree`
drops groups whose real twins disagree on a base name, which removes most of
that noise. Second, even when the twins agree, a wrapper's identity lives in
its callees: decode the `jal` targets on both sides and check that those are
twins too (or byte-compare them if unreconstructed) before renaming. The
validation set for the tool is the event overlays -- it must report
`bunit_initialize_menu_tile_and_line_primitives` /
`require_initialize_postbattle_unit_menu_primitives`,
`attack_apply_menu_palette_for_mode` / `bunit_apply_menu_palette_for_mode`
and `equip_clip_portrait_poly_from_left` /
`bunit_clip_portrait_poly_from_left` as strict twins (`--all-groups` shows
real-vs-real pairs).

Renames go through `scripts/rename_symbol.py`; afterwards the module's
`generated.ld` files are stale and `make build MODULE=<id>` must be re-run.

## Known failure mode: coroutine dispatchers

The detector splits stack-switching / coroutine dispatchers at their interior
`jr $ra`, emitting the tail half as a bogus standalone "function". Three
confirmed instances, all now in `config/skip-addresses.txt`:

| fragment   | belongs to dispatcher at |
| ---------- | ------------------------ |
| 0x80092b1c | 0x80092b04 (wldcore)     |
| 0x8014cf28 | 0x8014ceb4 (battle)      |
| 0x801003f8 | 0x80100384 (world)       |

The tell is unmistakable in the disassembly: no prologue, manual `$at`
construction, and `$ra` restored from a *global word* rather than the stack
(`lui at,0x8010 / addu at,at,zero / lw ra,0x042c(at)`). These are handwritten
assembly and are not reconstructable in C at all, so both halves are skipped.

If a discovered candidate looks like this, do not write a wip `.c` for it --
record it with the disassembly as evidence. The forced-boundary rule cannot help
here because neither half is a real function entry point.

