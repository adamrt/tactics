# Development environment

Docker is the only supported environment for extraction, compilation, linking,
disc construction, tests, and static analysis. This keeps the historical
compiler and every supporting tool pinned independently of the host system.

PCSX-Redux is the only intentional host-side tool. It consumes the disc image
under `build/disc/` and is not part of the Docker image.

## Tool policy

Project-owned binary tooling and orchestration are written in Go under
`cmd/tools/`. Python is used only by pinned third-party tools.

The historical `cc1` binaries expect preprocessed input. The build first runs
the container's MIPS preprocessor with system include directories disabled and
only `include/` enabled, then passes the deterministic `.i` file to `cc1`.

The Docker image contains:

- Go and native build tools;
- mkpsxiso/dumpsxiso 2.30;
- GNU MIPS binutils and GCC;
- the decompals PSX build of GCC 2.6.3;
- maspsx;
- Splat and spimdisasm for bulk binary and overlay analysis;
- m2c for initial C drafts;
- asm-differ for instruction-level comparison;
- decomp-permuter for reviewed last-mile matching experiments;
- the PSY-Q signature database; and
- qemu-i386 for the 32-bit historical `cc1` executables.

Downloads are pinned by release, commit, and/or SHA-256 digest in the
Dockerfile. Proprietary SDK files must never be added to the image or
repository.

## Symbol naming

Names describe the binary or overlay that owns code, rather than the source
directory that happens to contain it. Externally linked game functions use a
lowercase owner prefix such as `battle_`, `world_`, `wldcore_`, `bunit_`, or
`main_`; mutable globals use `g_<owner>_`. Project constants and enum values
use the corresponding uppercase owner or data-domain prefix.

The primary executable entry function is the sole game-code exception: it
remains `main` because GCC 2.6.3 emits the required call to `__main` only for
that spelling.

Project record aliases use lowercase snake case and a `_t` suffix, with a tag
without the suffix (for example, `struct battle_action_data` and
`battle_action_data_t`). Shared serialized formats use their data domain
instead of a false overlay owner: `party_data_t`, `entd_unit_t`, and
`gns_file_record_t` are examples. File-local implementation names are left to
the owning reconstruction unless exporting them would improve provenance.

Keep reviewed external APIs and their established names unchanged: Psy-Q/PSX,
Suzuki, libc, and other library-owned symbols listed in `config/libraries.yaml`.
Likewise, `FFT_` header guards remain project-wide include guards, not semantic
symbol prefixes. Shared encoded-text control constants use `TEXT_`.

Use `scripts/rename_symbol.py` for exported-function renames. It updates the
source path, module manifest, reviewed symbol inventory, linker bindings, and
callers together; follow it with the focused exact-byte build.

## Decompilation helper workflow

The helper commands are available inside `make shell`. They do not participate
in acceptance: `config/modules.yaml`, reviewed symbol files, and
the byte comparisons performed by `tools` remain the sources of truth.

Use Splat or spimdisasm to create investigation material under the ignored
`build/analysis/` tree. Use m2c output as a draft, replacing inferred names,
types, field accesses, and control flow with declarations supported by target
evidence. Use asm-differ while iterating on emitted instructions. When a
credible WIP reconstruction is close but differs in register allocation or expression
ordering, decomp-permuter can explore alternatives; its output must be reviewed
and cleaned before entering `src/`.

`make wip ACTION=draft` resolves a module through `modules.yaml`, verifies the
extracted target hash, converts a half-open runtime range to file offsets, and
runs spimdisasm plus m2c with PSX-specific settings. For switch-heavy routines,
its ignored m2c input normalizes intra-function jump labels and supplies
target-derived jump-table entries that remain inside the confirmed range.
`make wip ACTION=diff`
compiles through the canonical historical pipeline before invoking asm-differ.
Set `PROFILE=gcc-2.6.3_O0_aspsx-2.34` on `match`, `diff`, or `prepare` only
when a target range has focused evidence for that registered exception; the
default remains `gcc-2.6.3_O2_aspsx-2.34`. Prepared permuter workspaces retain
the selected profile for every candidate compile.
On a mismatch it also prints advisory context for the first differing
instruction, including size/alignment, function-boundary location, nearby
target/compiled words, delay-slot hints, and changed register fields. These
diagnostics are heuristics only; the byte comparison remains authoritative.
`make wip ACTION=prepare` creates and debug-validates a canonical compiler
workspace; `make wip ACTION=permute` runs it locally for a bounded duration.
Their generated files live under `build/analysis/decomp/`.

After extraction, `make bootstrap` also runs one advisory MIPS inventory pass
over every executable module described by `config/modules.yaml`. It writes
`build/analysis/inventory/mips-inventory.json` plus a short `README.txt` summary
with reviewed coverage, uncovered bytes, and likely call/branch targets. This
report is generated triage material, not a match claim; reviewed configuration
and documentation remain authoritative. Use `make analyze` to rerun the pass
without extracting again.

Splat remains available for future bulk analysis of a newly selected overlay.
It does not replace extraction, `modules.yaml`, or the reviewed symbol files.

For raw overlays that are not yet represented in `modules.yaml` (such as
`WORLD/WLDCORE.BIN`), generate a bounded assembly context before invoking m2c:

1. Run `spimdisasm singleFileDisasm` with the overlay file, load address, and
   confirmed byte range, writing into `build/analysis/decomp/`.
2. Change the generated `nonmatching` function label to `glabel` in a derived
   ignored file; m2c uses the latter to identify the function body.
3. Run m2c on that derived assembly and review every inferred global, type, and
   pointer expression before creating a tracked WIP.

This keeps large raw-overlay drafts reproducible without adding an unreviewed
module or replacing the authoritative manifest.

A helper result is never a match claim. Finish with `make wip ACTION=match`,
the appropriate `make build MODULE=...` check, and `make build`. Keep generated assembly,
contexts, Splat configuration, permuter work directories, and unsuccessful
experiments out of version control.

## Generated files

The user supplies `fft-us-scus-94221.bin` at the repository root. It is verified before
extraction and is ignored by Git.

`make bootstrap` writes the ISO contents and mkpsxiso project to
`build/extracted/`, then writes `build/extracted/inventory.json` with each ISO file's
path, LBA, size, SHA-256 digest, and PS-X EXE metadata where applicable. It
refreshes the inventory and the advisory MIPS analysis when the extraction is
already complete. Analysis output is written under the ignored
`build/analysis/inventory/` directory.

Build output is written under `build/`:

| Output | Command |
| --- | --- |
| `build/event/small.out` | `make build MODULE=small` |
| `build/main/scus_942.21` | `make build MODULE=main` |
| `build/battle/battle.bin` | `make build MODULE=battle` |
| `build/event/attack/attack.out` | `make build MODULE=attack` |
| `build/event/etc/etc.out` | `make build MODULE=etc` |
| `build/event/option/option.out` | `make build MODULE=option` |
| `build/event/bunit/bunit.out` | `make build MODULE=bunit` |
| `build/event/jobstts/jobstts.out` | `make build MODULE=jobstts` |
| `build/event/equip/equip.out` | `make build MODULE=equip` |
| `build/world/world.bin` | `make build MODULE=world` |
| `build/disc/fft-us-scus-94221.{cue,bin}` | `make build MODULE=disc` |

The entire `build/` directory is reproducible and ignored. Do not commit its
contents.

Matching functions compile independently. Builds use four workers by default;
set `JOBS=1` for serial diagnostics or another positive value for local
capacity. Successful section output is cached by preprocessed source, generated
linker script, compiler profile, and tool fingerprints under `build/cache/`.
The Dockerized Go build cache also persists there. Set `CACHE=0` to force a
cold matching-C rebuild; remove `build/cache/` to clear all project caches.

## Validation levels

`make doctor` checks the pinned Docker toolchain, while `make check-config`
validates the module, symbol, and linker manifests without rebuilding game
outputs. Both run inside Docker and are also invoked by `make bootstrap`.

`make test` covers project-owned Go logic. The Docker image pins the sole
compiler and assembler profile, and every module build verifies its output
against the target bytes.
`make build MODULE=...` enforces exact binary output for one module; selecting
`disc` builds every reconstructed module once and verifies the complete image.

`make build` combines these non-interactive checks. `make run` performs that
build and then launches the rebuilt disc in PCSX-Redux on the host.

## Parallel build race

`make build` compiles reconstructions with `TOOLS_JOBS` workers (four by
default). Under that parallelism a compile intermittently reads a truncated
preprocessed file and fails with `parse error at end of input`, a bogus
undeclared-identifier error, or a spurious byte mismatch in a function that is
actually correct. Re-running the identical command succeeds, and the function
that fails moves between runs.

When a build reports a mismatch, confirm it before believing it:

```sh
REPORT_ALL=1 CACHE=0 JOBS=1 make build
```

`JOBS=1` removes the race and `REPORT_ALL=1` lists every mismatching function
instead of stopping at the first, which turns "which reconstructions regressed?"
into a single build rather than one build per answer. A mismatch that survives
that run is real.

The same race is why `make wip ACTION=diff` occasionally fails right after a
file is written; retrying the identical command clears it.

## Verification builds cannot run while workers are drafting

`tools build` gates on manifest consistency: every `wip/**/*.c` must appear in
`config/wip.yaml`, or the build aborts with

```
tools: orphan C source wip/<module>/<name>.c is not in the wip manifest
```

A reconstruction worker writes its `.c` before its `.ld`, and scratch files come
and go across its iterations. `scripts/consolidate_wip.py` can only register a
draft once the `.ld` exists (that is where the address comes from), so a draft
mid-iteration is unregisterable *and* fatal to the build. Consolidating in a loop
does not help -- the next worker write re-breaks it.

This is not a bug to route around. Run the authoritative check at a wave
boundary, when no worker is running:

```sh
python3 scripts/consolidate_wip.py
REPORT_ALL=1 CACHE=0 JOBS=1 make build
```

Between waves, the per-function `make wip ACTION=match` gate is what establishes
that an individual reconstruction is byte-exact; the full build is what
establishes that the promoted set still links and that the disc image is
unchanged. Both are needed -- do not treat a green `make wip` as a substitute.

`make build MODULE=<id>` narrows the *build* to one module but still runs the
manifest gate first, so it does not sidestep the constraint.

Never delete a worker's scratch file to unblock a build; it may be the draft it
is actively iterating on. Wait, or register it once it has an `.ld`.
