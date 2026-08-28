# Reconstruction status

All addresses and file ranges below refer to the verified USA target described
in [target-disc.md](target-disc.md). Machine-code ranges are half-open in build
logic and inclusive when displayed in this document.

At this checkpoint, `config/modules.yaml` contains 1,330 matching
reconstructions covering 180,848 function bytes across 38 registered modules.
Run `make check-config` for live totals; this document is the only checked-in
human-readable coverage snapshot.

## Main executable

`SCUS_942.21` is a 356,352-byte PS-X EXE loaded at `0x80010000`. Its 2,048-byte
header means a text address maps to a file offset with:

```text
file offset = runtime address - 0x80010000 + 0x800
```

The production reconstruction contains 170 byte-matching C functions:

| Ownership | Functions | Function bytes | Scope |
| --- | ---: | ---: | --- |
| Square/game code | 134 | 18,548 | Startup/display, game-loop and overlay-loader flow, controller input, save-state/options and item-order defaults, status-check tables, new-game state, party/status/job-unlock/ability/action-data helpers, music/SFX wrappers, file/allocation helpers, OTAG glue |
| Psy-Q `LIBGPU` | 25 | 596 | Contiguous `PRIM.OBJ` packet helpers at `0x80023c68–0x80023ebb` |
| SUZUKI middleware | 11 | 140 | Two sound-state accessors and nine documented stub entry points |
| **Total** | **170** | **19,284** | Builds also verify 24 unique bytes of emitted data |

Third-party code is deliberately separated from the 134-function game-code
count. The authoritative per-function inventory is
`config/modules.yaml`. Before compilation, the build validates
target identity, source paths, generated linker inputs, compiler profiles,
sizes, address-to-file mappings, and overlap.

The generated executable is intentionally hybrid: ranges outside the matched
functions come from the extracted target. `make build MODULE=main` verifies every
declared range, then verifies the complete executable byte-for-byte.

### Startup and play-time state

The executable entry sequence at `0x80010a30` is the root of the in-executable
call graph. It clears BSS, establishes `sp`, `gp`, and `fp`, then calls the
byte-matching C `main` at `0x80040b88`. GCC 2.6.3 inserts `main`'s initial call
to the constructor runtime hook `__main` at `0x80010ad0`. The startup assembly
is an ABI boundary rather than an ordinary C function. `main` calls `startup`,
stores its current stack pointer in `g_game_loop_stack_pointer` at
`0x80047608`, and enters the byte-matching C `game_loop` at `0x80040a00`.
`game_loop` normally calls `startup2` unless the state at
`0x80045978` is 5. `startup` performs cold environment initialization, while
`startup2` performs game-state initialization and an optional warm-reentry
reset. Overlay paths call `game_reset` at `0x80040974`, which shuts down the
display/audio state, restores `g_game_loop_stack_pointer`, and jumps back into
`game_loop`.

The following reviewed names describe behavior directly established by the
target code:

| Address | Name | Established behavior |
| --- | --- | --- |
| `0x800459b8` | `g_play_time_frames` | Incremented once per VSync; rolls over at 60 |
| `0x800459bc` | `g_play_time_seconds` | Rolls over at 60 |
| `0x800459c0` | `g_play_time_minutes` | Rolls over at 60 |
| `0x800459c4` | `g_play_time_hours` | Increments up to a cap of 1000 |
| `0x8004d9b4` | `g_startup2_has_run` | Cleared by `startup`, tested and then set by `startup2` |

The first timer word is a frame remainder, not milliseconds. Save loading
decomposes the total-seconds value at save offset `0x120` into hours, minutes,
and seconds; it does not restore the frame remainder. `g_startup2_has_run` is a
descriptive reconstruction name, not a claim about the original source name.

## Battle overlay

`BATTLE.BIN` is a 1,397,096-byte raw overlay loaded at `0x80067000`; unlike the
main executable, it has no PS-X EXE header:

```text
file offset = runtime address - 0x80067000
```

Five hundred Square/game functions cover 52,600 function bytes with the same
canonical profile; builds also verify 264 unique bytes of emitted data. Coverage includes
the main 60-state battle loop, 31 of its
menu, movement, targeting, and action state handlers, game-flow and AT-list state, cursor and unit
movement, action-menu transitions,
controller and camera input, battle render initialization,
palette updates, formulas, sprite and
animation data access, real-coordinate animation, camera offset-coordinate snapshots,
coordinate/tile helpers, GNS map-state record selection, map texture- and palette-animation control,
map CLUT decoding and upload staging,
map lighting and background-color transitions, screen-color modulation snapshots,
ENTD load polling, status-screen and animation-speed state, teleport setup, and map
freeze/unfreeze and field-color wrappers,
weather-SFX lifecycle, and
battle-control/timing wrappers, effect-state initialization, and effect-file
section accessors. `make build MODULE=battle` validates the overlay
itself; `make build MODULE=disc` also reads it back at LBA 1000 before requiring the
complete disc SHA-256.

Across both files, named game-code coverage includes startup/display flow,
party and unit initialization, status/ability helpers, music/file/allocation
wrappers, and battle game flow, camera, rendering, and formula code. Names and
data types are promoted only when both the local FFHacktics snapshot and the
target code support them; provisional `func_` and `D_` names remain
intentionally visible.

## EVENT/SMALL.OUT

`EVENT/SMALL.OUT` has complete matching-C coverage of its executable range:

| Property | Value |
| --- | --- |
| Disc LBA | 2,000 |
| File size | 7,891 bytes (`0x1ed3`) |
| SHA-256 | `09e0892d94aacee21dcb3f0d3c154745dbc3b9de21c6de2df602d0560fbe260f` |
| Inferred load address | `0x801d7000` |
| Matching game C | 2 functions / 108 bytes (`0x0000–0x006b`) |
| Alignment | `0x006c–0x006f` |
| Data | `0x0070–0x1ed2` |

The load address has high-confidence static evidence: absolute references to
`0x801d7070`, `0x801d7074`, and `0x801d70ec` map directly to offsets `0x70`,
`0x74`, and `0xec`. It has not yet been confirmed dynamically.

`small_initialize_battle_text_pointers` installs the overlay's unit-name and
job-name string blocks in battle text-pointer slots 8 and 6, copies slot 22 to
slot 2, and clears script variable `0x39`. `small_return_zero` is the remaining
8-byte stub. Together they reconstruct every instruction in the file. The
alignment and non-code data tail remain preserved from the verified extracted
target. `make build MODULE=small` compiles both functions and verifies the complete
7,891-byte overlay; `make build MODULE=disc` also substitutes and reads it back at LBA
2,000.

## Additional overlays

The following raw overlays have focused matching-C builds. Every reconstructed
module is substituted into and read back from the exact disc build.

| File | Load address | Matching game C | Target |
| --- | --- | ---: | --- |
| `EVENT/SMALL.OUT` | `0x801d7000` | 2 functions / 108 bytes (complete code range) | `make build MODULE=small` |
| `EVENT/ATTACK.OUT` | `0x801bf000` | 36 functions / 3,652 bytes | `make build MODULE=attack` |
| `EVENT/ETC.OUT` | `0x801bf000` | 6 functions / 4,360 bytes | `make build MODULE=etc` |
| `EVENT/OPTION.OUT` | `0x801bf000` | 10 functions / 2,488 bytes | `make build MODULE=option` |
| `EVENT/BUNIT.OUT` | `0x801bf000` | 64 functions / 3,424 bytes | `make build MODULE=bunit` |
| `EVENT/JOBSTTS.OUT` | `0x801df000` | 48 functions / 2,500 bytes | `make build MODULE=jobstts` |
| `EVENT/EQUIP.OUT` | `0x801bf000` | 34 functions / 1,112 bytes | `make build MODULE=equip` |
| `EVENT/CARD.OUT` | `0x801bf000` | 86 functions / 23,080 bytes | `make build MODULE=card` |
| `EVENT/REQUIRE.OUT` | `0x801bf000` | 69 functions / 21,688 bytes | `make build MODULE=require` |
| `EVENT/DEBUGCHR.OUT` | `0x801bf000` | 34 functions / 14,916 bytes | `make build MODULE=debugchr` |
| `EVENT/HELPMENU.OUT` | `0x801df000` | 2 functions / 140 bytes | `make build MODULE=helpmenu` |
| `EFFECT/E071.BIN`, `E074.BIN`, `E259.BIN`, `E338.BIN`, `E373.BIN`, `E452.BIN`, `E464.BIN`, `E474.BIN`–`E478.BIN` | `0x801c2500` | 12 shared-helper instances / 1,440 bytes | `make build MODULE=effect259` (focused E259 build) |
| `EFFECT/E450.BIN`, `E453.BIN`–`E456.BIN`, `E458.BIN`, `E464.BIN`, `E480.BIN` | `0x801c2500` | 16 functions / 4,248 bytes | `make build` |
| `OPEN/OPEN.BIN` | `0x80067000` | 100 functions / 15,740 bytes | `make build MODULE=opening` |
| `WORLD/WLDCORE.BIN` | `0x80067000` | 30 functions / 2,196 bytes | `make build MODULE=wldcore` |
| `WORLD/WORLD.BIN` | `0x800e0000` | 111 functions / 7,872 bytes | `make build MODULE=world` |

Target-byte instruction signatures and the local routine maps establish the
full executable spans of `DEBUGCHR.OUT` and `HELPMENU.OUT`, excluding trailing
assets. Their focused builds now include exact starter batches:

| File | Load address | Code range | Mapped functions | Exact coverage |
| --- | --- | --- | ---: | --- |
| `EVENT/DEBUGCHR.OUT` | `0x801bf000` | `0x801bf000–0x801c523f` | 37 | 34 functions / 14,916 bytes |
| `EVENT/HELPMENU.OUT` | `0x801df000` | `0x801df000–0x801e05d3` | 4 | 2 functions / 140 bytes |

The corresponding `jr ra` counts in the target are exactly 37 and 4, matching
the local routine maps. `BONUS.BIN`, `BTLEVT.BIN`, the chapter/end/game-over
files, `ITEM.BIN`, `TEST.EVT`, `UNIT.BIN`, and `WIN001.BIN` have no executable
MIPS signatures and should be investigated as event-script or table formats.
`EVTCHR.BIN`, `EVTFACE.BIN`, `FONT.BIN`, `FRAME.BIN`, `MAPTITLE.BIN`,
`WLDFACE.BIN`, and `WLDFACE4.BIN` are graphics/font payloads. The `.LZW`
entries are compressed data, `SPELL.MES` is message data, and the listed
`DEBUGMAP.OUT` and `EVTOOL.OUT` entries are zero-length files.

The broader disc audit also found two omitted native-code families. `OPEN/OPEN.BIN`
is a game overlay loaded at `0x80067000`; its initial exact coverage includes
fade setup, transition-state initialization, hexadecimal decoding, pointer-offset
calculation, and compact script-control handlers. Exactly 111 files in the
`EFFECT/E000.BIN`–`E511.BIN` family contain native MIPS alongside effect data.
A relocation-free 120-byte scratchpad-vector helper is now exact in all twelve
overlays where it appears. The wiki heuristic that treats a small first word as
data misses leaf-code cases such as E259, E338, and E464, so target instruction
structure remains authoritative.

The complete EFFECT classification, naming convention, and reviewed wiki-range
corrections are recorded in [effect-overlays.md](effect-overlays.md).

`WORLD/WLDCORE.BIN` is a separate overlay from `WORLD/WORLD.BIN`, loaded at
`0x80067000`. Its first-class build currently covers four initialization/finalization
routines and 24 compact pointer, job-category, flag, menu-result, and no-op helpers. The listed non-code WORLD
payloads (`SNPLBIN`, `SNPLMES`, `WLDBK`, `WLDMES`, and `WLDPIC`) remain classified
as data; WLDCORE and WORLD are the two native-code-bearing WORLD files.

`JOBSTTS.OUT` contains 24,612 bytes of mapped MIPS code across 94 routines.
Its exact coverage includes job-point and job-level display state, ability
selection state, ability tabs, special-monster classification, job skillsets,
list-menu setup, encoded-string and render-command traversal, synchronized
VRAM transfers, graphics command parsing, and two byte-oriented bitstream
initializers.

`EQUIP.OUT` contains 61,660 bytes of mapped MIPS code across 179 routines.
Its exact coverage covers menu values and indices, item types, Two Swords
and Two Hands checks, transition frames, sprite color, speed scaling, and two
bit-reader initializers.

`ATTACK.OUT` controls pre-battle scenario and deployment flow. Its initial
matching coverage establishes event-thread wrappers, an unaligned signed
halfword reader used by scenario-condition parsing, two-slot scenario-music
loading and playback, selection between its deployment-coordinate slot blocks,
the 5-by-5 valid-deployment-tile matrix, and the full roster-fieldability and
deployment-squad selection routine. Additional compact coverage decodes packed
values, updates paired geometry-like fields, accesses an indexed record field,
initializes an offset-derived pointer table, advances an event thread in a
nonreturning loop, and removes the first matching entry from another 5-by-5
table.
Coverage also includes deployment-worker setup, paired forward/reverse roster
selection, cross-squad fieldability filtering, item graphic descriptors,
map-title image loading, and the contiguous `0x801c3ca8`-`0x801c3f44` block
that checks, removes, swaps, and resets entries in deployment-screen tables.
Four documented null routines are also exact C matches at `0x801c087c`,
`0x801c1f20`, `0x801c3070`, and `0x801c61dc`.

`BUNIT.OUT` currently covers special-monster detection, event-thread and input
state access, four offset-conservative unit-record getters, two compact render
command parsers, and the local unit/job data path: base-job resolution,
job-to-skillset lookup, job-wheel construction, and three-byte job-unlock storage. Its independently
exact output is also read back at LBA 2832 during `make build MODULE=disc`.

`WORLD.BIN` begins with data and linked graphics-library code; the documented
game-code routines begin at `0x800e1a88`. Its current matching coverage includes
thread scheduling/allocation, camera synchronization, event-instruction
navigation, signed `A0`–`A5` conditions and waits (the comparison handlers
consume the runtime operand stack and write their boolean result to operand 0),
item accessors, menu-input
selection, event RNG, parameter storage, script-variable storage, and
support-ability checks. Its load address follows the verified file mapping
`runtime address - 0x800e0000` and the local FFHacktics routine map.
Three additional documented empty routines at `0x800e7808`, `0x800f6f18`,
and `0x800fd074` are exact C matches.

Target-derived work maps a contiguous WORLD menu-graphics helper cluster:
the fixed quad initializer at `0x800e2398` (172 bytes), fixed sprite initializer
at `0x800e2444` (116 bytes), sprite-array loop at `0x800e24b8` (104 bytes),
image-load parameter copier at `0x800fda54` (80 bytes), graphic-rectangle setter
at `0x800fdb60` (40 bytes), menu text-origin setter at `0x800fdb88` (24 bytes),
the image draw-mode setter at `0x800fdba0` (196 bytes), the draw-mode setter at
`0x800fdc64` (116 bytes), image-loading setup at
`0x800fdcf0` (584 bytes), and the zero/no-op stubs
at `0x800fdcd8` and `0x800fdce0` (8 bytes each). These helpers are exact
matches and are now promoted. The adjacent menu sprite-array initializer and
menu-window pointer reset are exact at `0x800e24b8–0x800e2547`; the primitive
brightness setter at `0x800e289c` and the texture-allocation-grid reset at
`0x800e2c0c` are also exact.

## Disc image

`make build MODULE=disc` substitutes every generated module into the extracted
mkpsxiso project, checks the executable bytes at LBA 24, and requires the entire
raw disc image to have the target SHA-256:

```text
29e63bb6d2e7b842fe87f7c0ee03b7076681c34bcc47095cca27ec53236bf4f9
```

`make run` builds and launches this image in PCSX-Redux.
