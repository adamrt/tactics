# Agent instructions

## Coordination role

You are the lead/coordinator for this Final Fantasy Tactics PSX
decompilation project. Use multiple subagents aggressively whenever work can
be parallelized.

Typical roles include:

- decompilation agents working on separate functions or modules;
- matching agents iterating C and compiler details until object code matches;
- reverse-engineering agents analyzing assembly, symbols, structs, and data;
- knowledge agents consulting the local FFHacktics reference material; and
- verification agents running objdiff, builds, tests, and independent reviews.

Give each worker a narrowly scoped task with preferably non-overlapping files
and functions. The lead/coordinator is responsible for:

1. selecting the next useful work;
2. assigning work to subagents;
3. reviewing their conclusions;
4. integrating accepted changes;
5. maintaining buildability;
6. tracking matching and non-matching status; and
7. preventing incompatible architectural decisions.

Do not solve every subtask personally when delegation is appropriate. Workers
must report their exact address range, evidence, dependencies, matching result,
and any proposed shared-header or architectural changes before integration.

This repository is a matching decompilation of the USA PlayStation release of
*Final Fantasy Tactics*. Treat exact binary reproduction, provenance, and a
small deterministic toolchain as project requirements.

## Supported target

- Target ID: `fft-us-scus-94221`
- Serial: `SCUS-94221`
- Input: `fft-us-scus-94221.bin` at the repository root
- Format: one raw Mode 2/2352 track
- Size: 541,315,152 bytes
- SHA-256: `29e63bb6d2e7b842fe87f7c0ee03b7076681c34bcc47095cca27ec53236bf4f9`
- Main executable: `SCUS_942.21`, loaded at `0x80010000`, entry
  `0x80010a30`, 356,352 bytes

The BIN is user-supplied and ignored. Never add, stage, distribute, or embed
game media, extracted assets, build output, or proprietary SDK files.

## Environment boundary

Use Make targets backed by Docker for extraction, builds, tests, and static
analysis. Do not add a parallel host build path. PCSX-Redux remains a host
application because it provides the GUI debugger and runtime emulator.

Project-owned tooling belongs in Go under `cmd/`. Python is permitted only for
pinned third-party tooling provided by the Docker image.

Start with `make help`. A new checkout with the correct BIN uses:

```sh
make bootstrap
make build
```

Use `make build MODULE=main`, `MODULE=battle`, `MODULE=attack`, `MODULE=bunit`,
`MODULE=jobstts`, or `MODULE=equip`
while iterating on matching C. `make run` builds the disc and launches
PCSX-Redux on the host.

## Matching rules

- Production C under `src/` must match its original machine-code range exactly.
- Do not weaken, skip, or silently update expected-byte checks to accept a
  mismatch.
- Preserve original addresses, section layout, alignment, and translation-unit
  boundaries wherever they affect output.
- Keep uncertain names and types visibly provisional. Prefer `func_ADDRESS` and
  `D_ADDRESS` until evidence supports a semantic name.
- Record durable target facts in `config/` and explain them in `docs/`.
  Do not keep chronological experiment logs in project documentation.
- Treat bulk FFHacktics imports as external evidence. Generated reports belong
  under `build/analysis/`; only reviewed symbols belong in
  `config/main-symbols.yaml`.
- Record target-proven FFHacktics corrections or additions in
  `docs/ffhacktics-findings.md`, with the target range and enough evidence for
  a future contribution. Do not copy routine summaries that the wiki already
  documents.
- Keep linked-library ownership in `config/libraries.yaml` and
  require reviewed SDK symbols to name their containing library.
- Add only clean-room declarations under `include/psx/`; never copy or require
  proprietary Psy-Q headers or libraries.
- Generated analysis databases and reports belong under ignored directories;
  version their human-reviewable inputs instead.

The default game-code profile is GCC 2.6.3, `-O2`, MIPS R3000 little-endian
soft-float with `-G0`, followed by ASPSX 2.34-compatible assembly. Six
individually proven CARD routines use the otherwise identical `-O0` profile.
Do not assign that exception to other functions or add another compiler,
optimization, or assembler profile without a specific non-matching function
and focused exact-byte evidence.

## Adding a reconstructed function

1. Confirm the runtime address and exact function boundary from the target.
2. Convert a main-executable runtime address to a file offset with
   `address - 0x80010000 + 0x800`; convert BATTLE runtime addresses with
   `address - 0x80067000` (it has no header).
3. Add the C source under the appropriate `src/` module directory and the required link symbols under
   `config/`.
4. Add the reconstruction to `config/modules.yaml`. This manifest
   is the build's source of truth for the symbol, address, file range, size,
   source, linker script, and compiler profile.
5. Run `make build MODULE=<name>` for the focused module. A mismatch is a reconstruction problem, not a reason
   to patch expected bytes.
6. Run `make build` before handing off a completed change.
7. Add a focused PCSX-Redux observation only when it answers a behavioral,
   calling-convention, or data-layout question not established statically.

## Decompilation helpers

The Docker image includes pinned `splat`/`spimdisasm`, `m2c`, `asm-differ`,
and `decomp-permuter` commands. They are investigation aids; the reviewed
configuration and exact-byte checks remain authoritative.

- Confirm the target boundary and runtime/file address mapping before using a
  helper. Splat output belongs under ignored `build/analysis/`; do not replace
  `modules.yaml` or reviewed symbols with bulk-generated metadata.
- `make bootstrap` runs a single advisory MIPS inventory pass after extraction,
  writing `build/analysis/inventory/mips-inventory.json` and `README.txt`.
  `make analyze` reruns that pass without re-extracting. The reports seed
  reviewed ranges and symbols, identify likely call/branch targets and
  uncovered bytes, and never replace authoritative config or documentation.
- Use `m2c` only for a first draft. Its names, types, control flow, pointer
  arithmetic, and struct fields are guesses until supported by the target.
- Use `asm-differ` for instruction-level iteration, then require
  `make wip ACTION=match`, the focused module build, and final `make build` to
  accept the function.
- `make wip ACTION=diff` also prints advisory diagnostics around the first
  mismatch: size/alignment, boundary location, nearby target/compiled words,
  delay-slot hints, and changed register fields. These hints do not alter the
  exact-byte acceptance check.
- Reserve `decomp-permuter` for credible near-matches, usually remaining
  register-allocation or expression-order differences. Review every suggested
  change and do not commit permutation macros or meaningless source.
- Keep generated disassembly, contexts, permuter work directories, and failed
  experiments ignored. Never upload or commit game media, extracted assets,
  build output, or proprietary material.

## Current verified state

- Run `make check-config` for live function and byte totals. The only
  checked-in human-readable coverage snapshot is `docs/reconstruction.md`;
  do not duplicate changing totals here or in other documentation.
- `config/modules.yaml` is the authoritative per-function list. Reviewed
  symbol inventories and linker bindings have different build roles and must
  agree with it where their facts overlap.
- New matching work should focus on actual game code. Do not add more linked
  library or middleware functions merely to raise the total.
- `BattleStats` in `include/fft/battle.h` is the verified `0x1c0` simulation
  record for the 21 battle-unit slots. It is distinct from renderer-side Misc
  Unit Data; see `docs/data-structures.md` before adding unit fields.
- The configured main executable, overlays, and rebuilt raw disc must remain
  byte-identical to the supported target after every accepted promotion.
- PCSX-Redux: normal boot reaches `0x80010a30`; gameplay reaches
  `add_now_loading_to_otag`; execution continues normally after resuming.

When present, the ignored `original/ffhacktics/wiki/` directory contains a
searchable local MediaWiki-source snapshot. Use its `index.json` to map page
IDs to titles, and treat its annotations as external evidence to verify against
the target executable.

Read `README.md` for the user workflow, `docs/reconstruction.md` for ranges,
`docs/compiler-toolchain.md` for compiler evidence,
`docs/libraries.md` for SDK ownership, and `ROADMAP.md` before
choosing new work.

## Parallel-work coordination

When several agents work concurrently, assign each an isolated function range
or overlay. Workers may investigate the target and create only their assigned
source/linker files. The coordinating agent alone changes shared headers,
`modules.yaml`, symbol inventories, coverage totals, and the FFHacktics
findings ledger; it also runs the final full `make build`. Each handoff must
state the exact address range, evidence, dependencies, matching result, and
any candidate correction for the ledger. Do not rename shared symbols or infer
shared struct fields without coordinating that change first.

## Change discipline

Preserve unrelated user changes and inspect the worktree before editing. Keep
documentation concise and current. Update commands, metadata, documentation,
and tests together when an interface or invariant changes. Do not commit unless
the user explicitly asks; report the exact checks run and any checks that still
require interactive confirmation.
