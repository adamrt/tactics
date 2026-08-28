# FFHacktics contribution findings

This is a compact ledger of corrections or additions supported by the verified
US `SCUS-94221` target. Each item should be independently rechecked before
posting it to FFHacktics. Routine names and broad behavioral notes already
present in the wiki are not repeated here.

## E080 Zodiac routine boundary

The E080 routine described by page `00009789` owns runtime range
`0x801c306c–0x801c463b` (file `0x0b6c–0x213b`). Its `jr ra` at
`0x801c4634` is followed by the required delay-slot `nop` at `0x801c4638`.
The next routine begins at `0x801c463c`, not `0x801c4638`, and continues
through its own return delay slot at `0x801c4dac`. Page `00009790` and the
overview link on page `00009651` should therefore start the second routine at
`001c463c`. Treating `0x801c4638` as both the prior delay slot and the next
entry creates a four-byte overlap.

Evidence: US `EFFECT/E080.BIN`, file offsets `0x2128–0x2148`; FFHacktics
pages `00009651`, `00009789`, and `00009790`.

## Main executable level-up EXP store

The level-up check at `0x8005d880–0x8005d8fb` caps experience by storing
`99` at unit offset `0x21` in the instruction at `0x8005d8dc`. The local wiki
annotation describes that store as setting level to 99, but level is the
adjacent byte at offset `0x22`; the target instruction updates EXP.

Evidence: US `SCUS_942.21`, runtime address `0x8005d8dc`, and FFHacktics page
`00000553`.

## BATTLE.BIN weapon-characteristic Two Hands branch

The physical-attack support routine at `0x80186054–0x8018614b` skips the
Two Hands multiplier when weapon-characteristic bit `0x01` is set. The branch
at `0x80186064` jumps directly past the multiplier for a nonzero bit. The local
wiki annotation instead describes bit `0x01` as forcing Two Hands.

Evidence: US `BATTLE.BIN`, file offsets `0x11f054–0x11f14b`, and FFHacktics
page `00000457`.

## WORLD.BIN event-instruction-size table address

`Find Event Instruction Byte Offset` (`0x800fd34c`) indexes the
event-instruction-size table at effective RAM address `0x8013a454`. The
current disassembly annotation gives `0x8014a454`, but the target uses
`lui 0x8014` followed by `lbu ..., 0xa454(...)`; MIPS sign-extends that
displacement, yielding `0x8013a454`.

Evidence: US `WORLD/WORLD.BIN`, file offsets `0x1d37c–0x1d387`.

## WORLD.BIN thread-allocation upper bound

`Get Next Available Thread ID` (`0x800fd07c`) and `Find Next Inactive Thread`
(`0x800fd0d8`) test candidate IDs `1` through `16` inclusive. Their loop test
is `index < 17`, rather than the `index < 16` condition shown in the older
assembly annotations. An input below `16` is returned unchanged; `16` requests
an allocation search.

Evidence: US `WORLD/WORLD.BIN`, file offsets `0x1d07c–0x1d14b`.

## EVENT/OPTION.OUT: `0x001c00c0–0x001c00ff`

The instructions on the pages for `OPTION.OUT 001c00c0 - 001c00e4` and
`OPTION.OUT 001c00e8 - 001c00fc` label their stores as `0x801d9ce4…` and
`0x801d9cf4…`. That is one high page too high.

The retail words are:

```text
0x001c00c0: 3c01801d  lui r1, 0x801d
0x001c00c4: a4249ce4  sh  r4, 0x9ce4(r1)
```

MIPS immediates are sign-extended for the store offset, so the effective
address is `0x801d0000 + sign_extend(0x9ce4) = 0x801c9ce4`. The four-word
routine stores to `0x801c9ce4`, `0x801c9ce6`, `0x801c9ce8`, and `0x801c9cea`;
the two-word routine stores to `0x801c9cf4` and `0x801c9cf6`.

Evidence: verified `EVENT/OPTION.OUT` SHA-256
`0fcd32324e54e67549cb1ad9666a1e3fca953b1ef33592377eebe11b952e71e8`, file
offsets `0x10c0–0x10ff`, loaded at `0x801bf000`.

## EVENT/HELPMENU.OUT thread scan and saved pointers

The routine at `0x801dfdd4–0x801dfe0f` begins with thread ID 4 and tests IDs
4 through 8 inclusive. It compares each thread record's `is_running` word at
offset `0x48` with 1, rather than comparing the thread ID itself. Thus the
older “after 4” title and comparison comment are misleading; the exact C name
is `helpmenu_find_running_thread_at_or_after_4`.

The close routine at `0x801df000–0x801df04f` copies a saved 32-entry table of
text pointers from `0x801f7504` back to `g_battle_text_pointers` at
`0x80173f8c`. The source is a pointer table, not string contents. In the target
instruction that forms the source address, the destination register is `r5`,
not `r4` as stated by the older register comment.

The navigation records used by both large handlers are `0x10` bytes. Four
one-byte neighbor indices occupy offsets `+0x06…+0x09`; cursor X, cursor Y,
and orientation are signed halfwords at `+0x0a`, `+0x0c`, and `+0x0e`.
Consequently the older layout that begins those halfwords at `+0x08` overlaps
the neighbor array and is not the retail layout. `0x801e0b30` is a 32-entry
table of relative `u32` offsets, while the encoded text blob begins at
`0x801e0bb0`; `0x801f7504` is the separate saved text-pointer array.

Evidence: byte-exact US `EVENT/HELPMENU.OUT`, file ranges `0x0000–0x004f` and
`0x0dd4–0x0e0f`, static target ranges `0x0e10–0x15d7` and
`0x085c–0x0a3b`, plus FFHacktics pages `00010919`, `00010921`, `00010922`,
and `00012784`.

## EVENT/REQUIRE.OUT battle-unit name loop

The routine at `0x801cb21c–0x801cb2cb` iterates over all `0x15` (21) battle
unit records. The older page title/comment describes “Strings 8,” but the
target's loop bound is 21. Each selected pointer begins at record offset
`0x12c` and advances through the fixed `0x1c0`-byte battle-unit stride.

Evidence: US `EVENT/REQUIRE.OUT`, file range `0xc21c–0xc2cb`, and FFHacktics
page `00009040`. The routine remains a nonmatching semantic WIP, so the
existing shared `BattleStats` declaration is not changed on this evidence
alone.

## WORLD.BIN thread scheduler source order

Two source-level details are now established by exact C reproduction of the US
target, beyond the existing assembly annotations:

- `Stop Current Thread` (`0x800ffe28–0x800ffe63`) clears both `is_running`
  (`+0x48`) and `task_id` (`+0x4c`) before `Switch To Next Thread` begins. The
  second store occupies the `jal` delay slot, so a faithful C representation
  puts both assignments before the call.
- `Wait For Thread` (`0x800ffea0–0x800ffeeb`) is a `do … while` loop: it
  switches at least once, then tests `is_running`. It is not a pre-checked
  `while` loop.

The verified records use a `0x400`-byte thread stride. Evidence: matching C
under `src/world/`, target offsets `0x1fe28–0x1fe63` and
`0x1fea0–0x1feeb` in the US `WORLD/WORLD.BIN`.

## WORLD.BIN thread-context layout

`Initialize Thread` at `0x800ffd70–0x800ffdf3` matches the corresponding
documented BATTLE routine and establishes the shared context layout: global
pointer at `+0x38`, stack/frame pointers at `+0x3c/+0x40`, code pointer at
`+0x44`, `is_running` at `+0x48`, `task_id` at `+0x4c`, and cleared words at
`+0x0c` and `+0x50–+0x68`. The stack and frame pointers are initialized to
`thread + 0x3f0`, confirming a downward-growing per-thread stack.

Evidence: byte-exact `world_initialize_thread` in the US `WORLD/WORLD.BIN`,
file range `0x1fd70–0x1fdf3`.

## WORLD.BIN tutorial and camera synchronization

`Tutorial thread switching for Event Instructions` (`0x800e1d90–0x800e1de3`)
uses `0x80153320` as a scheduler countdown: it initializes it to `0xff`, yields
once per iteration, subtracts four, then clears it after the final yield.
`Run Camera Move Thread` (`0x800e1f28–0x800e1f57`) likewise yields at least
once, then waits until the battle-camera-active predicate at `0x8008e17c`
becomes zero.

Evidence: byte-exact C reconstruction of both US `WORLD/WORLD.BIN` ranges.

## BATTLE.BIN GNS record selection fields

The GNS loader's mesh-selection loops establish meanings that are obscured by
the older per-instruction comments. In each `0x14`-byte record, offset `0x00`
is passed to `Get Script Variable`, so it is a script-variable ID rather than
an opaque GNS header. Offset `0x02` is the signed comparison state. Offset
`0x04` is not weather: it selects the comparison (`1` equal, `2` requested
state less than record state, `3` requested state greater than record state).
Offset `0x05` is the resource type (`0x17` texture, `0x2e` primary mesh,
`0x2f` override mesh, `0x30` alternate mesh, `0x31` end).

The requested state uses the selected script variable's low 12 bits, script
variable `0x23` in bits 12–14 (weather), and script variable `0x24` in bit 15
(time-of-day). Thus bytes `0x04–0x05` also form the familiar little-endian GNS
type values such as `0x2e01`, but the game deliberately consumes their bytes
separately during selection.

The raw record layout also separates the 16-bit start-sector field at offset
`0x08` from an unknown halfword at `0x0a`; they are not one 32-bit LBA. The
32-bit byte length begins at `0x0c`, followed by unknown halfwords at `0x10`
and `0x12`.

Evidence: US `BATTLE.BIN`, runtime ranges `0x800f2618–0x800f3637`,
`0x8013b590–0x8013b6e3`, and `0x800f38e0–0x800f3bd7`, plus raw USA
`MAPnnn.GNS` records. The comparison helper, record processor, GNS bootstrap
loader, and script-variable getter/setter are byte-exact C reconstructions.

The adjacent wrapper at `0x800f36c4–0x800f3717` consumes a separate
`0x14`-byte map-file descriptor: offset `0x02` is its 32-bit LBA, offset `0x06`
is its 32-bit byte length, and byte `0x0d` gates whether the load is attempted.
Contrary to treating its fourth argument as incidental call-site state, the
wrapper deliberately preserves and forwards it to `load_data_from_disc` as
the loading-display suppression flag. The wrapper is a byte-exact C
reconstruction.

The map-mesh loader at `0x800f4acc–0x800f4dd3` confirms that resource `0x2e`
is the default mesh and resource `0x30` is a state-selected alternate. It scans
the same 20-byte GNS records, applies the established layout/weather/time
predicate to alternates, copies the selected record, and starts file slot
`0x30`. After the asynchronous read completes, it passes the loaded mesh data
to the renderer and frees the temporary allocation. The complete range is a
byte-exact C reconstruction.

The adjacent routine at `0x800f4dd4–0x800f5577` appends a mesh geometry block,
rather than copying an undifferentiated GNS section. Its callers are the
primary-mesh and eight animated-mesh cases in the resource dispatcher. The
four header counts are textured triangles, textured quads, untextured
triangles, and untextured quads. The six bulk groups are positions for all four
classes and normals for the two textured classes; the later halfwords inserted
into the position records are packed terrain-tile locations for textured
polygons. This ordering and the 9/12-halfword position/normal groups agree with
the target's `0x18`/`0x20` renderer record strides. The complete range is a
byte-exact C reconstruction named `append_map_mesh_geometry`.

The adjacent `0x800f5578–0x800f5983` routine is the paired runtime-record pass,
not another undifferentiated mesh copy. It skips those position and normal
groups, splits packed UV halfwords into byte coordinates, forms the CLUT
command as `(value & 0x3f) | 0x7800`, retains the texture-page halfword, and
initializes three state bytes for untextured polygons. Its `0x28`, `0x34`,
`0x14`, and `0x18` destination strides distinguish the four polygon record
classes. The complete range is a byte-exact C reconstruction named
`initialize_map_mesh_render_records`.

### Texture-animation handle ownership

The 32 words at `0x800f6ccc` are handles parallel to the 32 `0x14`-byte
texture-animation instructions copied from a mesh, rather than GNS-record or
mesh-resource entries. The texture-animation interpreter allocates the sole
nonzero handle through `0x800911f4`; map cleanup passes each handle to
`0x80091248` and clears it. The allocator's service table has eight
`0x0a`-byte records.

Evidence: US `BATTLE.BIN`, runtime ranges `0x800911f4–0x8009154b`,
`0x800f1204–0x800f2293`, `0x800f30f0–0x800f326f`, and
`0x800f5984–0x800f59ef`.

### Casting-state reset and deployment status

The short routine at `0x8013f4a8–0x8013f4f3`, called by the casting-unit
reset wrapper at `0x80070998`, resets event/unit state and clears the event
command globals after checking event thread 1. It is recorded as
`reset_battle_event_state`. The immediately following routine at
`0x8013f4f8–0x8013f51f` calls the thread-running predicate for thread 6 and
returns its result; the local FFHacktics annotation identifies this as the
deployment-screen running check, recorded as `is_deployment_running`.

The shared routine at `0x80142d58–0x801433a7` is called by that wrapper and
by event/menu paths. FFHacktics labels the range as performing extensive
event processing; it is therefore recorded provisionally as
`process_event_commands` until its arguments and sub-operations are
reconstructed.

The routine at `0x801a1244–0x801a1287` is the animation-tick companion
to `lookup_effect_timing_curve_value` at `0x801a1200`: it reads the effect
progress halfword at offset `0x28`, indexes by half, and uses the timing
curve's `+0x12c` region before extracting a nibble. The local wiki explicitly
distinguishes this second-half lookup; it is reconstructed as
`lookup_effect_animation_timing_curve_value`.

### Map transition state handlers

The loop’s `finish_battle_frame` helper at `0x800787dc–0x800787fb` is a
32-byte wrapper that calls `stop_map_texture_animations_and_weather_sfx`
(`0x800f5984`). Its focused battle build matches exactly.

The map-transition handlers following the main battle-state dispatch share a
fade primitive layout indexed by the screen-polarity slot. `MapJumpingOut`
(`0x800787fc–0x80078963`) increments the fade value and enters
`MapInitialize` (state `0x36`) at completion; `MapJumpingOut2`
(`0x80078964–0x80078acb`) uses the same layout and enters `MapInitialize2`
(state `0x39`). `MapInitialize` (`0x80078bf4–0x80078d1f`) and
`MapInitialize2` (`0x80078d20–0x80078e57`) call the shared map loader with the
map ID and loader mode, then use loader result `0x0d` to advance. The first
initializer enters `MapJumpingIn` (state `0x37`); the second restores the
previous game state after clearing its previous-state slot. `MapJumpingIn`
(`0x80078e58–0x80078fb3`) decrements the fade value and restores the previous
state when it reaches zero, resetting animation speed to one.
`MapJumpingIn2` (`0x80078fb4–0x8007929f`) performs the unit/camera and event
processing needed while the map is revealed, then uses the same decrementing
fade record. When the value reaches zero it clears the previous-state slot and
returns to that saved state; unlike `MapJumpingIn`, its body also dispatches
event-command results and updates status/animation helpers before drawing the
fade primitives.

Evidence: US `BATTLE.BIN`, runtime ranges above, and FFHacktics pages
`00003703`, `00003704`, `00003706`, `00003707`, and `00003708`.

The adjacent helper at `0x801a12a4–0x801a12db` indexes the effect-disc table
by `effect_id * 8` and copies its two words (LBA and byte length) to the
caller’s output pointers. This matches the local “Load LBA sector and Byte
length of effect” annotation and is tracked as WIP
`load_effect_lba_and_size`; the target has a distinctive stack adjustment
around its second store that the current draft does not reproduce.

The effect-preparation routine uses the halfword at `0x801b895c` as a
load/display countdown: it initializes it to `0x3c` when a targeted effect is
selected (or zero otherwise), decrements positive values once per call, and
uses a positive value to keep the effect state active. It is recorded as
`g_effect_load_countdown`, distinct from the effect phase at `0x801b63e8`.

The byte at `0x801c24c8` is the effect loader's state selector. The preparation
routine branches on values `0` through `3` for its load, reload, and secondary
effect paths, and writes those same values when advancing or failing a load.
It is recorded as `g_effect_load_state`, adjacent to the effect ID at
`0x801c24d0`.

The byte at `0x801bbf64` is the active effect target ID. The preparation
routine tests it before targeted-effect cleanup and passes it to the
secondary-effect loader; zero means that no effect target is selected. It is
recorded as `g_effect_target_id`.

The effect loader passes the fixed destination `0x801b3500` to the disc-read
helper for every selected effect before the data is parsed. This is recorded
as `g_effect_file_buffer`.

The halfword at `0x801b9134` is the current secondary-effect target being
animated. The secondary-effect removal path walks this ID separately from
the list head at `0x801b9130` and the currently processed target at
`0x801b9138`; it is recorded as `g_current_effect_animation_target_id`.

The complete 40-byte body of `is_deployment_running` is a minimal wrapper: it
calls `process_event_commands()`, then returns `is_event_thread_running(6)`.
A clean-room WIP draft now lives at `wip/battle/is_deployment_running.c`.

### JOBSTTS callback-table targets

The callback map on local FFHacktics page `00010076` has two incorrect
targets. The target callback table at `0x801e506c` assigns slot `0x04` to
`0x801df9b4`, not `0x801df974`, and slot `0x07` to `0x801dfa6c`, not
`0x801df694`. These values are read directly from the US `JOBSTTS.OUT`
callback table and agree with the routine boundaries on page `00010042`.

Evidence: US `EVENT/JOBSTTS.OUT`, runtime table at `0x801e506c`, and
FFHacktics pages `00010042` and `00010076`.

The current-job summary globals referenced by `0x801df964–0x801dfa6b`
likewise require signed-low-half correction. The target's `lui 0x8020`
instructions combine with negative offsets `0xa5b0–0xa5c4`, so the effective
addresses are `0x801fa5b0–0x801fa5c4`, not `0x8020a5b0–0x8020a5c4`.

Evidence: US `EVENT/JOBSTTS.OUT`, runtime range
`0x801df964–0x801dfa6b`.

The selected specific-ability-data pointer used by the routines at
`0x801df9b4–0x801dfb1b` is at effective address `0x801f0050`, not
`0x801eff50`. The target loads upper half `0x801f` with positive offset
`0x0050`, and the ability classifier at `0x8005a72c` writes its output pointer
to that slot before both JOBSTTS consumers dereference it.

Evidence: US `EVENT/JOBSTTS.OUT`, runtime ranges
`0x801df9b4–0x801dfa23` and `0x801dfab8–0x801dfb1b`; FFHacktics pages
`00010031` and `00010035`.

The selection-state clear routine at `0x801df4a4–0x801df4df` passes a byte
length of `0x06` to `memset`; this clears one six-byte record, not six words as
the local page comment states. The adjacent store routine also addresses its
five-record table at effective address `0x801fa530`. Its annotated
`0x801f1f30` address is inconsistent with the target's signed low-half
addressing and the verified six-byte stride.

Evidence: US `EVENT/JOBSTTS.OUT`, runtime range
`0x801df4a4–0x801df52b`, and FFHacktics pages `00010016` and `00010017`.

### EQUIP sign-extended data addresses

Several local EQUIP disassembly annotations visually combine an upper
`0x801f` with a negative signed low half as though the effective address also
began with `0x801f`. MIPS sign extension makes the target addresses one
64-KiB page lower. The verified effective addresses are `0x801e8fec`,
`0x801e8ff8`, `0x801e905c`, `0x801e9060`, and `0x801e92e4`.

Evidence: US `EVENT/EQUIP.OUT`, runtime ranges `0x801c894c–0x801c8993`,
`0x801c9604–0x801c9667`, `0x801cd558–0x801cd567`, and
`0x801cdf50–0x801cdf87`.

### Memory-card BIOS event descriptor address

The memory-card event setup instruction at main-executable address
`0x800457d4` stores the BIOS eject-event descriptor at `0x800596cc`. The local
FFHacktics comment identifies `0x800596c8`, but that preceding word holds the
BIOS busy-event descriptor. The four BIOS descriptors at
`0x800596c0–0x800596cc` are consumed in order by the CARD overlay event-polling
routine at `0x801c3fa4–0x801c409b`.

Evidence: US `SCUS_942.21`, runtime range `0x800457c8–0x800457db`; US
`EVENT/CARD.OUT`, runtime range `0x801c3fa4–0x801c409b`; and FFHacktics page
`00003099`.

### REQUIRE battle-nickname string count

The routine at `0x801cb21c–0x801cb2cb` serializes nicknames for all 21 battle
unit slots, not eight strings as the local FFHacktics title states. Each output
name consumes at most 16 bytes and is terminated with `0xfe` when the source
does not already contain a `0xfe` or `0xff` terminator.

Evidence: US `EVENT/REQUIRE.OUT`, runtime range
`0x801cb21c–0x801cb2cb`, and FFHacktics page `00012759` (redirected from
`00009040`).

### ETC polygon dimensions and buffer selection

The chapter-graphic dimension records used by
`0x801bf3e0–0x801bfc57` have a `0x0c`-byte stride with height, X, and Y at
offsets `0x06`, `0x08`, and `0x0a`. The offsets shown on local page
`00012781` would extend beyond that stride. The first index of the primitive
workspace is the caller's frame counter masked with one, establishing
double-buffer parity rather than screen polarity.

The same page's ETC directory summary stops at `end4.bin`, but the target
table contains a thirteenth entry for `end5.bin` at `0x801c0880`. Entries
8–12 have null dimension pointers and texture mode 2; the async display path
dispatches the polygon builders only for modes 0 and 1, so the chapter
dimension table is not used by the ending graphics. The game-over builder
also consumes its dimension records with swapped axes, rather than the
chapter-field interpretation suggested by the shared page labels.

Evidence: US `EVENT/ETC.OUT`, runtime range
`0x801bf3e0–0x801c03ab`; FFHacktics pages `00006933`, `00010923`, and
`00012781`.

### ITEM.BIN logical size and transfer allocation

`EVENT/ITEM.BIN` is `0x8200` logical bytes: `0x8000` bytes of sprite pixels
followed by a `0x0200`-byte CLUT block. The `0x8800` constant described as its
file size on local page `00005122` is instead the 17-sector rounded transfer
allocation; the last `0x0600` bytes are padding outside the logical file. This
distinction agrees with the disc index and with the separate pixel and palette
uploads at offsets `0x0000` and `0x8000`.

Evidence: US `EVENT/ITEM.BIN`, file ranges `0x0000–0x7fff` and
`0x8000–0x81ff`; US `WORLD/WORLD.BIN`, runtime range
`0x80106204–0x80106247`; FFHacktics pages `00002205` and `00005122`.

### BUNIT ability-list local call ownership

The call at `0x801c749c` in BUNIT's ability-list builder targets
`0x801c71d4`, the local BUNIT implementation of the skillset-to-first-job
lookup. Local page `00010271` labels that target as the JOBSTTS implementation,
but the two overlays merely contain analogous routines at different load
addresses.

Evidence: US `EVENT/BUNIT.OUT`, runtime range `0x801c7498–0x801c74a3`;
FFHacktics pages `00009927` and `00010271`.

### JOBSTTS transition-frame and ability-CT callbacks

The JOBSTTS routines at `0x801e456c` and `0x801e457c` are the setter and
getter for a signed transition-frame counter. The setter is not an
ability-category switch as suggested by the master-page annotation: callers
initialize the counter to zero, advance it through rendering frames, and set
it to ten to disable transition scaling. Ability category is stored
separately at `0x801e5232`.

The callback at `0x801dfab8` computes the displayed cast-turn value for an
ability: it reads the ability secondary-data CT byte at offset `0x0c`, returns
`ceil(100 / CT)`, and adds the menu display flags encoded by the selected
ability entry. It is installed into the JOBSTTS callback table rather than
being an abilities-menu opener itself.

The neighboring callbacks at `0x801dfa6c` and `0x801dfb1c` provide the
displayed MP and JP costs. They read ability-secondary-data byte `0x0d` and
ability-data halfword `0x00`, respectively, and add the same packed renderer
flags. Their legacy “opening a job's abilities menu” descriptions identify the
surrounding UI but not the routines' callback roles.

Evidence: US `EVENT/JOBSTTS.OUT`, runtime ranges
`0x801dfab8–0x801dfb1b` and `0x801e456c–0x801e458b`; FFHacktics pages
`00000809`, `00000810`, `00010007`, `00010034`, `00010035`, `00010036`,
`00010042`, `00010058`, `00010070`,
`00010073`, `00010076`, and `00010080`.

### CARD text ordering-table index

The CARD state at `0x801d91dc` is an ordering-table index, not glyph advance.
The textured-quad builder multiplies its final argument by four, indexes the
ordering table, and links the emitted `POLY_FT4` there; every graphics-command
caller supplies `0x801d91dc` in that position. Consequently the command parser
at `0x801c6564` and setter at `0x801c69c4` set the text ordering-table index.

Evidence: US `EVENT/CARD.OUT`, runtime ranges `0x801c5a04–0x801c5ab7`,
`0x801c6564–0x801c657b`, `0x801c69c4–0x801c69d3`, and
`0x801c7d04–0x801c7e07`; FFHacktics pages `00010875` and `00010908`.

The pointer stored at `0x801d91d4` is the active render ordering-table entry.
The setter at `0x801c3dcc` receives ordering-table entry 1 from the current
graphics context, and the following renderer copies it into each render
descriptor before linking generated primitives. The encoded-text renderer at
`0x801c6c50` rasterizes a sentinel-terminated list of text IDs into a caller's
image buffer; its row-upload caller at `0x801c70ac` then transfers each
16-pixel-high result to VRAM.

Evidence: US `EVENT/CARD.OUT`, runtime ranges
`0x801c3dcc–0x801c3ddb`, `0x801c6c50–0x801c6ed7`, and
`0x801c70ac–0x801c71b3`; FFHacktics pages `00010825`, `00010841`,
`00010843`, `00010844`, `00010886`, `00010887`, `00010888`, and
`00010893`.

### Main music tempo-scale and formation preparation roles

The SUZUKI routine described as `Shift Balance` on page `00002664` operates
the current music record's tempo-scale interpolation tuple. Root-counter
updates apply that scale to the base tempo to obtain the effective tick rate,
and the SMD tempo command manipulates the same fields. The Square wrapper at
`0x80043c3c` therefore sets a timed tempo-scale change; the adjacent wrappers
at `0x80043c88` and `0x80043cd4` independently control pitch and stereo
balance.

The wrapper at `0x8005d5bc` prepares a temporary battle-unit record for the
Formation screen. Its `(unit, 1, 0)` call rebuilds derived job, equipment,
reaction/support/movement, and elemental fields while skipping live critical
and status-transition processing and preserving inflicted statuses. This is
more specific than the `Initialization?` note on page `00000550`.

Evidence: US `SCUS_942.21`, runtime ranges `0x80043c3c–0x80043d1f` and
`0x8005d5bc–0x8005d5df`; US `WORLD/WORLD.BIN`, caller at `0x80115360`;
FFHacktics pages `00000550`, `00000603`, `00002584`, `00002664`, `00002679`,
`00002685`, `00003050`, `00003051`, `00003052`, and `00005249`.

### BATTLE particle-emitter interpolation data

The four routines at `0x801a8c14–0x801a8df3` interpolate three-component
particle-emitter fields: spawn position, spawn spread, velocity base angles,
and velocity direction spread. The active particle renderer confirms these
roles through its subsequent position randomization and rotation-matrix
velocity construction. The target loads the spawn-spread fields as signed
halfwords even though the local particle-format page labels them unsigned.

The effect-header section at offset `0x10` is animation-curve data, and the
section at offset `0x0c` is particle-system data. The routines at
`0x801a1044` and `0x801a1078` set global pointers to those sections; they do
not return coordinate or motion-data addresses as their legacy labels imply.

Page `00003650` is titled for `0x801a8c8c` but duplicates the body at
`0x801a8c14`; page `00003651` contains the actual `0x801a8c8c` body. Page
`00007226` also describes `(index * 5) << 5` as `index * 120`, while the
instructions compute a 160-byte animation-curve-record stride.

Evidence: US `BATTLE.BIN`, runtime ranges `0x801a1044–0x801a10ab` and
`0x801a8c14–0x801a8df3`; FFHacktics pages `00003650`, `00003651`,
`00004641`, `00004642`, `00007226`, and `00012328`.

### REQUIRE display-condition helpers

The routine at `0x801c3ba4` waits up to a caller-supplied number of frames,
refreshing the controller-zero input pointer after each event-thread yield and
returning early when input bit `0x20` is set. It is the skippable wait used by
the READY and post-battle message flows, rather than an anonymous timer.

The REQUIRE display-condition dispatcher at `0x801cafd4` maps condition 5 to
permanent Brave/Faith changes and condition 6 to removal of units whose Brave
or Faith crosses the departure threshold. Those handlers share arrays of
affected battle-unit indices, message IDs, and message arguments. The target
walks the unit-index array as contiguous 32-bit elements; the old draft's
`[i * 4]` expression multiplied that stride a second time.

The permanent-change producer at `0x801c3fa4` scans all 21 battle-unit slots,
updates both original and current Brave/Faith values, and collects warning
records. The departure collector is the distinct range
`0x801c43e8–0x801c473f`; `0x801c4740` starts another post-battle routine, so a
range ending at `0x801c4ab4` incorrectly merges two functions. The shared
value at `0x80165ef4` feeds text substitution and carries several identifier
kinds in other overlays, so an affected-unit-specific global name is too
narrow.

Evidence: US `EVENT/REQUIRE.OUT`, runtime ranges
`0x801c3ba4–0x801c3c0f`, `0x801c3fa4–0x801c473f`,
`0x801c4ab4–0x801c4ec3`, and
`0x801cafd4–0x801cb15b`; FFHacktics pages `00006108`, `00006901`,
`00007062`, `00007285`, `00007286`, and `00009038`.

The same caller audit identifies `0x801bf01c` as a scaled draw-area packet
builder, `0x801c07b4` and `0x801c11b0` as post-battle unit-menu primitive and
palette initialization, `0x801c20d0` as that flow's simple-selection renderer,
and `0x801c2dcc` and `0x801c8b94` as scaled `POLY_FT4` geometry and
`POLY_GT4` color helpers. Overlay address collisions must not be treated as
identity: EQUIP also has code at `0x801c2dcc`, but its bytes differ from
REQUIRE beginning at the second instruction.

The bio-update table at `0x801d0adc` contains 11 records, each with three unit
class IDs and one script-variable ID. The page comment describing a `< 12`
loop is inconsistent with the target's comparison against 11, and the
routine's callers write lifecycle codes 12 through 15 rather than only the
unit-loss case named by the page.

Evidence: US `EVENT/REQUIRE.OUT`, runtime ranges
`0x801bf01c–0x801bf1f3`, `0x801c07b4–0x801c09d3`,
`0x801c11b0–0x801c132b`, `0x801c20d0–0x801c2243`,
`0x801c2dcc–0x801c300f`, `0x801c3a08–0x801c3aaf`, and
`0x801c8b94–0x801c8d37`; FFHacktics pages `00006084`, `00006090`,
`00006101`, `00006106`, `00006901`, `00007286`, `00009034`, and
`00009035`.

### Altima teleport-arrival effect 0xB8

The target routine at `0x8008a780` selects effect `0xB8` when the acting Misc
Unit Data record has spritesheet ID `0x41`, and the routine-specific page
identifies that path as Holy Angel/Altima teleport arrival. The general spell
list instead labels `0xB8` only with the PSP name "Infernal Strike." The
target call context and routine-specific disassembly establish teleport-arrival
behavior for the PSX effect ID; the general-list label should not override it.
The paired spritesheet-ID `0x49` path uses effect `0x28`.

Evidence: US `BATTLE.BIN`, runtime range `0x8008a780–0x8008a7ff`;
FFHacktics pages `00003823`, `00003826`, and `00000150`.

### WORLD resume-text parameter value

The resume-text routine changes a thread task ID from `0x33` to 1 and stores
`0x0000ffff` in the thread's second parameter. The annotation that describes
that stored parameter as signed `-1` is incorrect: the target constructs the
value with `ori v0,zero,0xffff` and performs a 32-bit store, so the upper 16
bits are zero rather than sign-extended.

Evidence: US `WORLD/WORLD.BIN`, runtime range
`0x80106834–0x80106867` (especially `0x80106858–0x8010685f`); FFHacktics
pages `00005132` and `00010212`.

### Main allocator free boundary

The `game_free` routine includes the `nop` at `0x8004466c` as the delay slot
of its `jr ra` at `0x80044668`. Its half-open function range is therefore
`0x80044600–0x80044670`; an end address of `0x8004466c` omits an emitted
instruction. The next reviewed routine starts at `0x80044670`.

Evidence: US `SCUS_942.21`, runtime range `0x80044600–0x8004466f`;
FFHacktics page `00003073` and the reviewed `clear_game_allocator_table`
entry at `0x80044670`.

## WLDCORE indexed-global addressing form

Resolved: `WORLD/WLDCORE.BIN` and `OPEN/OPEN.BIN` were assembled with an ASPSX
older than 2.30, which keeps an indexed global address in `$at` across four
instructions instead of folding `%lo` into the load. See
[compiler-toolchain.md](compiler-toolchain.md) for the evidence and the
registered `gcc-2.6.3_O2_aspsx-2.21` profile.

An earlier hypothesis that this could be reached from C by pinning the base
address into a register is wrong: the pin does produce the four-instruction
form, but in a general-purpose register, whereas the target uses `$at`, which no
compiler allocates.

## SCUS geomancy table is data, not code

`0x8004f1d0` ("Geomancy_tiles_type_to_ability_table") is 64 bytes of zero
padding, not a routine. It should be classified as data rather than carried as
an unreconstructed function.

## OPEN.BIN script-parser routines needing a real C reconstruction

Three OPEN.BIN routines have only ever been matched by writing the whole body as
inline assembly, which the project does not accept. They are unclaimed and their
drafts have been discarded:

| Address | Size | Name |
| --- | ---: | --- |
| `0x8006ffe4` | 60 | audio-control script opcode 0x7a |
| `0x80070020` | 60 | audio-control script opcode 0 |
| `0x8006bb74` | 296 | birthday-menu record initialiser |

The first two pass a sign-extended script operand, scaled by four, to
`open_set_sound_type_and_volume` and then advance `g_open_script_byte_offset` by
four. The third performs indexed field stores into the birthday-menu record
array at `0x80085d08` and the render-record array at `0x80086098`.

Retry these under `gcc-2.6.3_O2_aspsx-2.21`: OPEN.BIN carries 287 instances of
the older assembler's `$at` addressing form, and the inline-assembly spelling
predates that profile, so it may simply have been working around the wrong
assembler version.

## OPEN.BIN inline-assembly workarounds are now removable

Several already-matching `src/open/` files (for example
`open_bin_0006b0a4_0006b354.c`) carry hand-written `__asm__` macros that expand
an indexed global access into the `$at` form by hand. That was a workaround for
the canonical 2.34 profile folding `%lo` into the load.

With `gcc-2.6.3_O2_aspsx-2.21` registered, those expansions come from the
assembler and the inline assembly is unnecessary. Each such file should be
rewritten as ordinary C, rebuilt under 2.21, and re-verified byte-exact. Find
them with:

```sh
grep -l '__asm__' src/open/*.c
```

## Wiki entries that are not standalone functions

The routine-listing pages on the wiki carve some overlays at label boundaries
rather than function boundaries, so a handful of "routines" are really tail
fragments of a larger enclosing function. They have no prologue, read callee-saved
registers and stack slots they never write, and end in a bare `j` to the next
label. They cannot be compiled independently and should be excluded from the
candidate pool — the enclosing function reproduces them when it is reconstructed.

Confirmed fragments (verified by disassembly, not just a failed match):

| Address    | Wiki name              | Enclosing function ends at |
| ---------- | ---------------------- | -------------------------- |
| 0x80080c40 | Two Digit Experience   | `j func_80080EFC`          |
| 0x80080d84 | Two Digit JP           | `j func_80080EFC`          |

`scripts/regen_batches.py` and the ad-hoc pool generator both carry a `SKIP` set;
add addresses here and there together.
