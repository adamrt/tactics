# Data structures

This page records project-owned layouts that are sufficiently evidenced to use
in matching C.  A descriptive field name is a claim about the target; unknown
regions therefore remain explicit padding rather than being guessed.

## Indexed data records

`include/fft/data.h` defines records for the main executable's indexed data
and ENTD files. Their sizes are established by exact target routines, not
inferred from their names: `party_data_t` is `0x100` bytes (20 records at
`0x80057f74`), `item_data_t` is 12 bytes (`0x80062eb8`), and `job_data_t` is 48
bytes (`0x800610b8`).

`item_data_t` has a verified, primary-table layout: palette, sprite ID, required
level, type flags, secondary-data ID, type, two attribute/unused bytes, a
little-endian `u16 price` at `0x08`, shop availability, and a final unused
byte. The layout is corroborated by both exact lookup code and FFHacktics'
item-data documentation.

## Item-type order tables

The range `0x80057b20–0x80057b5b` is one `0x3c`-byte aggregate containing
seven signed-byte order lists, rather than one flat array. The exact
initializer and the load-game overlay establish these member boundaries:

| Aggregate offset | Capacity | Bytes restored from a save |
| ---: | ---: | ---: |
| `0x00` | 12 | 12 |
| `0x0c` | 8 | 8 |
| `0x14` | 8 | 7 |
| `0x1c` | 8 | 5 |
| `0x24` | 8 | 5 |
| `0x2c` | 8 | 7 |
| `0x34` | 8 | 5 |

Each initialized list is terminated by signed byte `-1`. The load routine
addresses all seven destinations independently, while the next structure—the
weapon item-ID page order—begins at `0x80057b5c`. The members remain numbered
in C because the target proves their layout and order-list role, but not yet
the semantic category represented by each list.

## ENTD encounter data

An `entd_unit_t` is a static `0x28`-byte unit definition stored in the four
`ENTD#.ENT` files. An `entd_encounter_t` contains 16 entries and is therefore
`0x280` bytes; an ENTD file contains 128 encounters and is `0x14000` bytes.
This directly explains the `event_id * 0x280` indexing in `get_entd` and the
`0x14000` allocation/read in `open_entd`.

`initialize_unit` selects one `entd_unit_t`, stores its address in the SCUS
current-ENTD pointer at `0x80066238`, and passes it with a temporary
`BattleStats` record to the battle-data initializer. This confirms that the
pointer addresses a single `0x28`-byte entry, rather than an encounter or file.

`entd_unit_t` is the input to the SCUS unit initialization pipeline. It is not a
`party_data_t` record (persistent roster state), `BattleStats` (runtime
simulation state), or the BUNIT menu record. The current type names the
fields read by the documented initializers: sprite, flags, job and skillset
IDs, R/S/M abilities, equipment, palette, position, direction, experience,
reward modifiers, and AI/target IDs. Unused bytes remain padding.

The exact initializer at `0x8005e478` establishes that the ENTD position word
stores Y in bits `0–7`, two facing bits in `8–9`, flags in `12–13`, and the
higher-elevation bit in `15`. The runtime `BattleStats` word keeps the same Y,
flag, and elevation positions but reserves all four bits `8–11` for facing.
The same routine proves ENTD offsets `0x1e` and `0x1f` as the war-trophy and
bonus-money values copied to `BattleStats` offsets `0x163` and `0x164`.

The Heretic toolkit's ENTD parser is a useful semantic cross-reference for
the file format, but target disassembly and exact matching remain the evidence
required for this project. In particular, its higher-level flag labels are
not promoted until the corresponding US target consumers confirm them.

`party_data_t` now names its verified `0x00–0xd0` prefix: identity/job and
equipment at the front, raw stats, job unlocks, learned abilities, job levels,
JP, name data, the name ID, and proposition availability. The matching
`ATTACK.OUT` fieldability routine proves that offset `0xd0` is nonzero while a
roster unit is unavailable on a proposition. The remaining `0x2f` bytes
intentionally stay unidentified.

## ATTACK deployment squads

`AttackSquadData` is the 12-byte deployment-area record addressed by
`EVENT/ATTACK.OUT`. The exact fieldability routine proves the record stride,
its map ID at `0x09`, and its unit limit at `0x08`; the valid-deployment-tile
accessors and FFHacktics deployment tables corroborate the 5-by-5 bitmap at
`0x00`. Coordinates, orientation flags, and placement ID retain descriptive
names based on the same ATTACK data-table documentation.

## Job IDs and event-condition opcodes

`include/fft/job.h` records only job-ID bounds and ranges directly established
by matching code and the local FFHacktics job map: legal data-table IDs are
`0x00–0x9f`, Squire is `0x4a`, and the special-monster ranges are
`0x3c–0x49` and `0x90–0x9a`. `include/fft/event.h` names WORLD event-condition
opcodes `0xa0–0xa5` by their observed signed comparison semantics. These are
constants, not a claim that the surrounding records or every opcode family is
fully mapped.

`include/fft/battle.h` also names the documented Target Current Action
HP-damage bit (`0x80`) and the renderer horizontal-flip value (`0x02`).

`BattleRealCoords` is a three-word renderer coordinate record in X, Z, Y
order. The current coordinates (`0x800e4e74`), saved snapshot (`0x800a1c5c`),
and per-frame delta (`0x800b72f4`) all use this layout. The matching BATTLE
animation routines establish that a `u16` countdown at `0x8009616a` controls
per-frame delta application.

The battle camera also preserves a `BattleRealCoords` offset-screen vector:
the renderer source is `0x800a77b0` and the camera snapshot is `0x800c7cb8`.
Exact copy, restore, and accessor helpers establish the pair without asserting
that either vector is a full camera record.

## `BattleStats`

`BattleStats` is the simulation-side, per-unit battle record.  It is exactly
`0x1c0` bytes.  The 21-slot array starts at `0x801908cc` while BATTLE.BIN is
loaded.  A slot’s `entd_slot` byte at offset `0x001` is `0xff` when absent.

It is distinct from `BattleMiscData` / “Misc Unit Data,” the renderer-side
record.  Misc Unit Data has 16 active `0x440`-byte slots; its documented
`0x148`-byte prefix stores a `BattleStats *` at offset `0x134`.
`BattleDisplayUnit` remains a compatibility alias while matching sources
migrate to the specific name.

The maintained C definition is [include/fft/battle.h](../include/fft/battle.h).
It contains a compile-time size check and currently names these useful regions:

| Offset | Region |
| --- | --- |
| `0x000–0x04d` | identity, job, palette, equipment, primary stats, position |
| `0x04e–0x071` | innate/current statuses, status CT, elemental affinities |
| `0x072–0x095` | raw stats and R/S/M flags |
| `0x096–0x158` | unlocked jobs and learned abilities |
| `0x15c–0x16d` | KO, charging, sprite, AI, and ENTD-derived data |
| `0x16e–0x18b` | action target data, unit state, and ability CT |
| `0x18c–0x1b7` | temporary battle-action results |
| `0x1b8–0x1bf` | autobattle state and inflicted-status bytes |

Use a `BattleStats *` when a routine operates on this record.  Retain a local
byte-address expression only if replacing it changes matching code generation;
the type still documents the function boundary in that case.

The byte at `0x15e` is presently undocumented padding.  Its presence places
the sprite ID at `0x15f`, the ENTD-derived war-trophy flag at `0x163`, and the
ENTD-derived bonus-money modifier at `0x164`; these offsets are directly
confirmed by `Initialize Unit's X/Y+Facing/Battle Rewards`.

## `BattleMiscData`

`BattleMiscData` is the rendering and movement record for an active map unit,
not the simulation record above. The maintained prefix names the sprite IDs and
display flags; world, screen, and movement coordinates; facing; mount state;
the `BattleStats` backlink; and the two status-flag words. Its prefix has a
compile-time `0x148`-byte size check. The remainder of the `0x440`-byte slot is
deliberately left outside the declaration until it is documented.

This distinction matters for source readability: `unit->map_x` is a renderer
coordinate at Misc offset `0x07c`, whereas `unit->x` is a simulation coordinate
at Battle Stats offset `0x047`.

### Evidence

- FFHacktics, local snapshot: `Battle Stats` and `Miscellaneous Unit Data`.
- `Get Battle Stats from Battle ID` multiplies its index by `0x1c0` and bases
  the result at `0x801908cc`.
- Existing exact functions validate the named `current_status`,
  `last_ability_id`, `ability_ct`, and `sprite_palette` offsets.

## MAPnnn.GNS records

The initial GNS table is an array of `0x14`-byte `gns_file_record_t` values, defined
in `include/fft/map.h`. BATTLE's loader reads the record's first halfword as a
script-variable ID. For mesh selection it combines that variable's low 12 bits
with weather (`script variable 0x23`, bits 12–14) and time-of-day (`0x24`, bit
15), then compares the result with the signed state at record offset `0x02`.

Record bytes `0x04–0x05` have two simultaneous views. As a little-endian
halfword they are the familiar GNS type values such as `0x1701` (texture),
`0x2e01` (primary mesh), and `0x3101` (end). The game reads byte `0x04`
separately as the state comparison (`1` equal, `2` requested less than record,
`3` requested greater than record) and byte `0x05` as the resource type.

Offset `0x08` is a 16-bit start sector relative to the MAPnnn.GNS base LBA;
offset `0x0a` is a separate, currently unknown halfword. Offset `0x0c` is the
32-bit byte length, while offsets `0x10` and `0x12` remain unknown halfwords.
The raw records and target halfword accesses rule out treating `0x08–0x0b` as
one 32-bit LBA.

`battle_get_script_variable` establishes the special handling behind this
packing. A request for variable `0x22` first reads variable `0x24` as the
one-bit time-of-day value and variable `0x23` as the three-bit weather value,
then stores `(time << 15) | (weather << 12)` back to `0x22` before evaluating
the requested variable. It preserves the active event operand word across the
operation, so the word reached through `0x80165f9c` is temporary interpreter
state rather than persistent map storage.

`process_map_gns_record` performs the corresponding record-level selection.
On phase `2`, resource types `0x85`, `0x86`, `0x88`, `0x89`, `0x8a`, and
`0x8b` dispatch directly; other records dispatch only when their comparison
accepts the assembled layout/weather/time state. The dispatcher establishes
`0x85`/`0x86` as indoor/outdoor changes, `0x88`/`0x89` as snow-off/snow-on,
and `0x8b` as a weather-modifier update. Type `0x8a` reaches its no-op path.

The matching adjacent `battle_set_script_variable` uses the same temporary
operand word and interpreter command interface. It also confirms that variable
`0x2c` is capped at `99,999,999`, matching the wiki's War Funds annotation.

`load_map_gns_and_move_find_items` indexes a four-byte GNS-LBA table and a
separate `0x10`-byte-per-map Move-Find/Trap table. It clears `0xbb8` bytes at
the fixed GNS-record buffer, then reads the first `0x1000` bytes of MAPnnn.GNS
into the allocated map-data buffer. `load_move_find_item_data` copies the
selected 16-byte entry verbatim to the current-map record at `0x80193910`.

The subsequent map-file loading path indexes a separate `0x14`-byte descriptor
table. `start_map_file_load` checks the presence byte at offset `0x0d`, passes
the 32-bit LBA at `0x02` and byte length at `0x06` to the shared disc loader,
and returns the destination only when that operation starts successfully. Its
fourth argument is forwarded as the disc loader's loading-display suppression
flag; its first argument is unused by this wrapper.

`load_map_mesh_variant` makes the mesh choice used by the event-side map
refresh path. It first retains the last primary-mesh record (`0x2e`), then
replaces it with an alternate-mesh record (`0x30`) when that record's
layout/weather/time predicate matches. The selected 20-byte record is copied
verbatim before its processed load descriptor at offset `0x06` is used to load
resource slot `0x30` into a temporary `0x20000`-byte buffer.

`append_map_mesh_geometry` consumes the geometry block used by the primary
mesh and each of the eight animated-mesh resource slots. Its first four
halfwords count textured triangles, textured quads, untextured triangles, and
untextured quads. It appends positions for all four classes and fixed-point
normals for the textured classes to renderer tables with `0x18`- and
`0x20`-byte records. After skipping the 10/12-byte textured-polygon records and
4-byte untextured-polygon records, it copies the packed terrain-tile location
for each textured polygon. Metadata offsets `0x88–0x96` retain each class's
starting index and incoming count before the four persistent totals advance.

`initialize_map_mesh_render_records` makes a second pass over the same block
at the current render-record totals. It skips the position and normal groups,
then decodes each textured triangle's five-halfword record and each textured
quad's six-halfword record. Packed UV halfwords become separate `u` and `v`
bytes; the low six bits of the following CLUT value are combined with
`0x7800`, and the texture-page halfword is retained verbatim. The destination
record strides are `0x28` for textured triangles and `0x34` for textured
quads. Untextured triangle and quad records use `0x14` and `0x18` strides; the
routine clears their first two state bytes and sets the third byte to one.
Those three untextured fields remain conservatively named because their wider
renderer semantics are not yet established.

## Map texture-animation runtime state

The mesh header's texture-animation chunk contains 32 instructions of `0x14`
bytes each. BATTLE copies those instructions to `0x80121d7c` and maintains a
parallel 32-word handle table at `0x800f6ccc`. The handle table is therefore
indexed by texture-animation instruction, not by GNS record.

The animation service at `0x800911f4` allocates eight records with a
`0x0a`-byte stride and returns a one-based handle, or zero when all slots are
active. The allocation path proves byte fields for `active`, elapsed frames,
and frame duration at offsets `0x00`, `0x01`, and `0x02`, followed by three
halfwords at `0x04`, `0x06`, and `0x08`. Its update routine rotates polygon
texture/render data over the selected polygon range, supporting the
provisional names `polygon_group`, `first_polygon`, and `last_polygon` for
those halfwords. The bulk reset clears the active byte in all eight slots. The
per-frame caller at `0x800912a4` is one function through `0x8009259b`, not a
series of helpers at the internal labels found in older annotations. It
updates texture, mesh, and palette animation state and related map lighting,
so `update_map_animations` is a provisional descriptive name for the whole
routine.

Palette animation has a separate runtime table at `0x800995f6`. Each loaded
mesh uses a `0x982`-byte bank containing 16 animation slots with an eight-byte
stride. `stop_map_palette_animation` clears the active byte for either one
selected slot or all 16 slots in a selected mesh bank. libFFT independently
identifies mesh-header offset `0x70` as the palette-animation instruction
pointer; that corroborates the resource kind, while the target routine proves
the runtime bank and slot layout.

The complete per-mesh palette bank begins at `0x800995f4`. Its first two bytes
are an unknown byte and an update-disable flag, followed by the 16 eight-byte
animation states at offset `0x02`. At offset `0x82`, it holds 256 seven-byte
color records: raw five-bit red, green, and blue components plus the one-bit
alpha flag at offsets `0x00–0x03`, with three bytes still unknown. The final
`0x200` bytes at offset `0x782` mirror all 256 packed PlayStation
`ABBBBBGGGGGRRRRR` CLUT words. `extract_palette_colors` fills one 16-color row
in that bank and in the mesh's `0x200`-byte upload staging bank at
`0x800e4ea4`. `load_map_palette_data` loads one row or all 16, first cancelling
the corresponding palette animations, and sets the upload-pending word at
`0x800995ec`. The consumer at `0x80092f98` transfers the staging buffer to VRAM
and clears that word.

`stop_map_texture_animation` preserves the target's unusual one-based handle
validation and `handle * 0x0a` byte access; that routine deliberately retains
a raw byte-array view until the apparent one-slot displacement is explained.
The map cleanup routine stops every recorded handle, clears all 32 words, and
also stops the three retained weather SFX IDs.

Evidence: US `BATTLE.BIN` runtime ranges `0x800911f4–0x800927bb` and
`0x800f30f0–0x800f326f`, the exact reconstructions at
`0x800911f4–0x800912a3`, `0x8009259c–0x800927bb`, and
`0x800f5984–0x800f5aeb`, FFHacktics' local
`Maps/Mesh` page, and libFFT's independently working mesh-header offsets.

## Map lighting and background transitions

The event-facing wrappers at `0x8009349c–0x80093503` accept a transition mode,
frame duration, and signed RGB components. `set_map_darkness` forwards those
values to the routine FFHacktics identifies as Map Darkness.
`modify_map_background_gradient` forwards the same shape to the separate
background-gradient transition system.

Three adjacent two-argument wrappers accept a frame duration and packed color
bytes. `set_map_background_gradient` consumes two RGB triples, matching the
top and bottom gradient colors in the mesh lighting chunk.
`set_map_ambient_light_color` consumes one RGB triple, matching the ambient
light field. `set_map_darkness_color` controls the third single-color
transition state used by the darkness system. The deeper transition routines
retain fixed-point current values and per-frame deltas; they have not yet been
reconstructed.

Evidence: US `BATTLE.BIN` runtime ranges `0x80090048–0x800911f0` and
`0x8009349c–0x80093653`, exact wrapper reconstructions, FFHacktics' `Maps/Mesh`,
`Color BG Beta`, and `Map Darkness Wrapper` pages, and the call from the
documented asynchronous Map Darkness event instruction.

## WORLD.BIN thread record

`WORLD.BIN` indexes its thread array with `thread_id << 10`, establishing a
`0x400`-byte record stride. The exact scheduler batch establishes the following
fields: three 32-bit function parameters at `0x00`, `0x04`, and `0x08`; a
saved global pointer at `0x38`; stack and frame pointers at `0x3c` and `0x40`;
a thread code pointer at `0x44`; `is_running` at `0x48`; `task_id` at `0x4c`;
and seven cleared 32-bit values at `0x50–0x68`. The local `WorldThread`
declaration under
`src/world/world_types.h` names only those verified facts; the remaining
bytes stay padding until direct evidence supports further fields.

## WORLD.BIN event operand buffer

The global pointer at `0x80153280` addresses the active event-script operand
buffer. The exact `A0`–`A5` condition dispatcher reads its first two signed
words and replaces word zero with, respectively, `>=`, reversed `>=`, `==`,
`!=`, `<`, or reversed `<`. The global’s wider type and lifetime are not yet
established, so matching sources declare only the pointer shape they use.

## BUNIT.OUT unit-data references

`EVENT/BUNIT.OUT` has a distinct, still-incomplete unit-data representation.
Its local pointer table begins at `0x801ecaf8`; exact routines establish a
job-code byte at offset `0x74`, a signed fallback job ID at `0x24`, gender
flags at `0x04`, and the learned-ability data passed to job-unlock calculation
at `0x64`. These fields are expressed by the partial `BunitUnitData` prefix
in `include/fft/bunit.h`, which deliberately has no claimed total size. Do not
treat it as `party_data_t`, `entd_unit_t`, or `BattleStats`; its full stride,
ownership, and lifetime remain unestablished.
