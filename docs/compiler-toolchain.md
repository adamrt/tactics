# Selected compiler toolchain

The default matching profile for FFT game code is:

```text
GCC 2.6.3
-O2
ASPSX 2.34-compatible assembly
MIPS R3000, little-endian, soft-float, -G0
```

This is the repository's canonical game-code profile. Most independently
matching functions provide the primary selection evidence. Nineteen CARD routines,
at `0x801bf170`, `0x801c09b4`, and from `0x801c3f04` through `0x801c4fb7`, use the same pinned pipeline with
`-O0`; each exception is assigned per function and does not change the
default.

## Why this profile

The production build is the evidence check. Every function registered in
`config/modules.yaml` is compiled with its declared profile and compared
byte-for-byte with its target range; declared emitted data sections are checked
the same way. Run `make check-config` for live totals and see
[reconstruction.md](reconstruction.md) for the sole checked-in coverage
snapshot. A complete build also requires every reconstructed module and the
final disc image to remain exact.

The selected tools are pinned in the Docker image. Project builds use the
open-source PSX GCC binaries from decompals/old-gcc and maspsx to reproduce the
required assembler behavior.

The repository does not claim this proves Square's exact historical patch
release or rules out local compiler changes. It defines the deterministic
toolchain used by this reconstruction.

## CARD `-O0` exceptions

The CARD routines at `0x801bf170`, `0x801c09b4`, `0x801c3f04`, `0x801c3f34`,
`0x801c3f6c`, `0x801c3fa4`, `0x801c409c`, `0x801c4144`, `0x801c41ac`,
`0x801c42a4`, `0x801c434c`, `0x801c43b4`, `0x801c447c`, `0x801c4550`,
`0x801c477c`, `0x801c4ab8`, `0x801c4bb4`, `0x801c4e1c`, and `0x801c4eec`
use frame pointers, spilled locals,
loop-preheader jumps, load-use nops, and unscheduled delay slots. GCC 2.6.3
`-O0` reproduces all nineteen ranges exactly. With every other pipeline input held
fixed, `-O2` emits compact versions identical in size to their optimized
main-executable analogues and differs from each CARD target at or near the
prologue. This evidence supports the nineteen explicit profile assignments; it does
not establish an overlay-wide optimization setting.


## WORLD tutorial-command `-O0` exceptions

The same `-O0` shape shows up in `WORLD.BIN`. The tutorial-command handlers
`handle_tutorial_command_wait` (`0x8012e720`),
`handle_tutorial_command_wait_time` (`0x8012ea44`), and
`handle_tutorial_command_shift` (`0x8012ddc8`) all match under
`gcc-2.6.3_O0_aspsx-2.34` and not under `-O2`, with the same frame-pointer
prologue that identifies the CARD group. A fourth,
`handle_tutorial_command_change_dialog` (`0x8012dfe4`), is `-O0` too on every
instruction except one constant grouping, and is parked in `wip/world/`.

Four adjacent handlers is suggestive but still short of proof that the whole
tutorial-command family is `-O0`, so the profile stays assigned per function,
like the CARD exception. Practically: when a `WORLD.BIN` target shows a
frame-pointer prologue and an otherwise un-optimized shape, try `-O0` before
concluding the function is unmatchable. The remaining handlers in this address
neighborhood are the obvious next candidates.


## WLDCORE/OPEN ASPSX 2.21 exception

`WORLD/WLDCORE.BIN` and `OPEN/OPEN.BIN` were assembled with an ASPSX older than
2.30. Below that version the assembler expands an indexed global access to a
four-instruction sequence that keeps the address in `$at`:

```text
lui   $at, %hi(sym)
addiu $at, $at, %lo(sym)
addu  $at, $at, index
load  reg, 0($at)
```

From 2.30 onward the assembler folds `%lo` into the load and emits three
instructions instead. GCC 2.6.3 emits the same assembler macro in both cases, so
this is not expressible in C and not a compiler-flag difference.

Evidence:

- `return_from_job_determinations` at `0x80079184` is a byte-exact 136-byte match
  under `gcc-2.6.3_O2_aspsx-2.21` and 132 bytes (mismatched) under the canonical
  2.34 profile, from identical C.
- `bar_menu_idle_routine` at `0x8006c3dc` matches the same way at 112 bytes.
- A binary scan for the `lui $at` / `addiu $at,$at` / `addu $at,$at,rX` triple
  finds 2,093 occurrences in `WLDCORE.BIN` and 287 in `OPEN.BIN`, against zero in
  `BATTLE.BIN`, `WORLD.BIN`, and every `EVENT/*.OUT` overlay. `SCUS_942.21` has
  six, which are not yet explained.

The profile is therefore assigned per function, like the CARD `-O0` exception,
rather than per module: some already-matching WLDCORE functions contain no
indexed global access and match under either assembler version. Use
`PROFILE=gcc-2.6.3_O2_aspsx-2.21` on `make wip` and pass `--profile` to
`scripts/promote_wip.py` when a WLDCORE or OPEN function needs it.

## Per-function matching

The canonical profile is a project-wide baseline, not permission to force a
near-match into the build. A semantic reconstruction can still differ solely
because the target leaves a call delay slot empty while GCC schedules the next
branch into it. First confirm that the struct layout, ABI declaration, and
ordinary C control flow are correct. If the difference remains, do not change
the global compiler flags or introduce raw assembly just to fit that function.
Leave it outside `modules.yaml` until focused evidence identifies a
deterministic, narrowly scoped profile, as with the CARD exceptions above.

## Open question: is there an `-O1` group in WORLD.BIN?

Two WORLD.BIN functions parked for the permuter, `world_func_80114088`
(`0x80114088`) and `world_func_80126374` (`0x80126374`), share a signature that
neither registered profile produces:

* branch delay slots left empty (`bnez` / `nop` / `li a0,1` / `jal` / `nop`),
* no strength reduction of loop address arithmetic -- the target recomputes
  `sll` / `addu` each iteration where `-O2` hoists an induction variable.

`-O0` is plainly wrong for them: it emits a frame-pointer prologue and, on
`world_func_80114088`, 136 bytes against a 52-byte target. `-O2` is right in
structure and wrong in exactly these two respects. That is the `-O1` signature.

A `gcc-2.6.3_O1_aspsx-2.34` profile is registered in `cmd/tools/config.go` so the
hypothesis can be tested, but **it has not been confirmed and no function is
assigned to it.** Registering a profile is not evidence; only a byte-exact match
is, exactly as with the CARD `-O0` and WLDCORE `2.21` exceptions.

To test it, the toolchain image must be rebuilt first -- `tools` is baked into
the image, so a new profile is invisible until then:

```sh
make _docker-build
make wip ACTION=match TARGET=... SOURCE=wip/world/world_func_80126374.c \
     LINKER=wip/world/world_func_80126374.ld OFFSET=... BYTES=... \
     PROFILE=gcc-2.6.3_O1_aspsx-2.34
```

If neither function matches, delete the profile rather than leaving an
unsupported option in the config for someone to reach for.

## Known maspsx gap: `lwl`/`lwr` pairs under the 2.21 emulation

`maspsx --aspsx-version=2.21` applies its `nop_lw_lw` rule between an `lwl` and
`lwr` of the same register even inside `.set noreorder`. The real ASPSX 2.21 did
not: `OPEN.BIN` at `0x8006c7f4` has the pair back to back.

Consequence: `open_bin_0006c750_0006c8a4` has a correct plain-C form that cannot
match under the 2.21 profile until maspsx exempts `lwl`/`lwr` pairs, so it stays
on the 2.34 profile with hand-written `$at` blocks. Fix the emulation, not the
source.

