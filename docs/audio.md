# Audio system

This page records the current evidence for the USA PlayStation release's audio
pipeline.  It describes the target, not a proposed replacement implementation.
The user-supplied disc files remain ignored; this document contains no game
media.

## Overview

FFT uses a Square/Suzuki sequencer on top of the PlayStation SPU.  Music and
most effects are sequenced instructions, not streamed PCM:

```text
WAVESET.WD                    SPU-ADPCM wave bank and instrument defaults
      | upload waveform region to SPU RAM
      v
Suzuki driver                 timer-driven sequencer and voice allocator
      ^                         ^
      |                         |
MUSIC_00.SMD ... MUSIC_99.SMD  SYSTEM.SED / ENV.SED / effect-file feds sections
music instruction streams      effect instruction streams
```

The target's linked `LIBSPU` range is Psy-Q support code.  The Suzuki layer is
separate middleware/game code which drives it; see [libraries.md](libraries.md).
The physical SPU supplies 24 voices, 512 KiB of sound RAM, SPU-ADPCM playback,
per-voice ADSR, stereo volume, noise, pitch modulation, and reverb.  The
hardware details needed for a clean-room mixer are documented by
[psx-spx](https://psx-spx.consoledev.net/soundprocessingunitspu/) and the
[PlayStation hardware manual](https://psx.arthus.net/sdk/Psy-Q/DOCS/Devrefs/Hardware.pdf).

## Disc assets and boot-time loading

The `SOUND/` directory contains one shared `WAVESET.WD`, `SYSTEM.SED`,
`ENV.SED`, and 100 `MUSIC_*.SMD` files.  The extracted inventory records their
exact sizes and hashes; it is generated and ignored.

The documented `open_permanent_sound_files` routine does the following:

1. initializes the Suzuki/SPU state;
2. reads `WAVESET.WD`, uploads its waveform region to SPU RAM, and retains its
   metadata in main RAM;
3. loads and registers `SYSTEM.SED` and `ENV.SED`; and
4. preloads five short SMDs numbered 45 through 49.

This sequence is corroborated by the target routine map and by the existing
matching `startup` reconstruction, which invokes `open_permanent_sound_files`
after the initial SPU reverb disable.  The local FFHacktics references are
`SCUS OpenGnrcSFX`, `Put WAVESET.WD in SPU`, and `Open Permanent sound files`.

## `WAVESET.WD`: samples and instruments

`WAVESET.WD` begins with the literal `dwdsP`.  The target header gives:

| Offset | Meaning | Target value |
| --- | --- | --- |
| `0x08` | whole-file size | `0x78b30` |
| `0x10` | waveform-region offset / header size | `0x0b30` |
| `0x14` | waveform-region size | `0x78000` |
| `0x18` | transfer offset used by the loader | `0x0b30` |
| `0x30` | instrument-definition array | documented as `0xb0` entries of `0x10` bytes |

The loader uses offsets `0x18` and `0x14` as the source offset and transfer
length, respectively.  That is direct static evidence that bytes
`0x0b30..0x78b2f` are copied into SPU RAM.

Each documented 16-byte instrument entry includes a wave/start pointer, ADPCM
repeat address, and the attack, decay, sustain, and release settings used to
construct an SPU ADSR envelope.  The local `WAVESET.WD` page also catalogues
the observed instrument IDs and names.  Two bytes in that entry (`0x06` and
`0x07`) remain unnamed.  The precise meaning of the top-level field at `0x28`
also remains provisional.

The bank should be treated as raw SPU-ADPCM data, not as a set of standalone
`.VAG` container files.  SPU-ADPCM uses 16-byte blocks and has in-band loop
start/end flags; the bank's repeat-address metadata and the hardware flags
both matter for accurate playback.

## `MUSIC_*.SMD`: sequenced music

Every `MUSIC_*.SMD` starts with `smds` and represents one song.  It contains a
header, a filename string such as `music_01.mid`, a table of per-channel
offsets, and concurrent channel instruction streams.  The following fields
are established by file inspection and driver use:

| Offset | Meaning |
| --- | --- |
| `0x00` | magic `smds` |
| `0x08` | complete file size |
| `0x14` | channel count |
| `0x1a..0x1d` | song reverb mode, volume depth, delay, and feedback |
| `0x1e` | filename offset |
| `0x20` | instruction-data offset |
| `0x22` | `u16` channel-offset table, terminated by zero |

When an SMD is started, `SuzukiPutPlaySMD` allocates a `MUS` block of
`0xb8 + channel_count * 0x160` bytes, copies SMD header values into it,
initializes each channel, and inserts the block into the Suzuki playback
state.  The existing exact `SuzukiGetActiveChannels` independently confirms
the `0xb8` channel-array offset, `0x160` channel stride, `MUS+0x16` channel
count, and a per-channel active-voice bitmask at `+0x34`.

The game wrapper `set_current_music_track` unloads a forced/current track when
needed, opens an SMD into one of two scenario-music slots, and switches to it.
The volume wrappers call `SuzukiCalcMusVolChange`, so timed fades are part of
the original driver behavior rather than a frontend-only feature.

### Known instruction families

The SMD interpreter and its 128-entry dispatch table are documented in the
local wiki.  The confidently named instructions include:

- notes, rests, note extension, channel end, octave changes, repeat/coda
  control, and tempo;
- instrument selection and reset to the WAVESET defaults;
- dynamics (volume), balance (pan), reverb enable, and song acoustics;
- ADSR shape/rate/level changes;
- LFO/pitch-shift and SPU noise controls; and
- calls that start ordinary or VFX sound effects.

The note-duration table and many handlers are traced from the target code.  A
number of implemented opcode handlers still lack semantic names, and the
exact behavior of time-signature, coda/to-coda, several control opcodes, and
the exact tempo conversion need dynamic confirmation.  Do not infer that an
unknown handler is unused merely because a name is missing.

## `feds` / SED effect data

`SYSTEM.SED` and `ENV.SED` both begin with `feds`.  Their headers directly
identify a file size, effect count, SED ID, and the start of the effect data:

| File | Size | Count | Data offset |
| --- | ---: | ---: | ---: |
| `SYSTEM.SED` | `0x212a` | `0xa8` (168) | `0x2b4` |
| `ENV.SED` | `0x083a` | `0x1b` (27) | `0x0080` |

The wiki's newer effect-file analysis identifies a second, more detailed
`feds` section used by visual-effect resources.  It contains a resource ID,
paired channel offset streams, and SMD-like instructions.  A timeline selects
a sound configuration; that configuration selects a pair of sequencer
channels; the resulting streams select instruments and drive SPU voices.  This
explains why effect playback can use the same note, envelope, dynamics, pan,
pitch, and loop machinery as music.

The general structure and the effect-file channel-pair mechanism are strong
evidence, but the full permanent-SED record schema is not yet project-verified.
In particular, the remaining SED header fields, all SFX mapping/priority rules,
and some VFX resource relationships should remain provisional.

## Cinematic streaming

The Suzuki path does not cover every sound-producing asset.  The disc also has
`OPEN/ENDING.XA`, and the `OPEN.BIN` routine map contains separate CD/movie
streaming paths for the opening and ending movies (`Stream Opening Movie`,
`Stream FFTST.STR`, and `Stream FFTEND.STR`).  This is strong evidence for a
second, CD-XA/STR-era cinematic audio path, but the project has not yet derived
the exact container layouts, XA coding parameters, or how its output is mixed
with the SPU sequencer.  A host port must either implement that path or replace
movie playback as a separately validated subsystem.

## Related but non-audio `*.SEQ` files

`BATTLE/TYPE*.SEQ`, `WEP*.SEQ`, and `EFF*.SEQ` are unit/weapon/effect animation
sequences.  Their command streams can trigger a sound ID, but they are not
Psy-Q `SEQ` music files and should not be routed through a generic PS1 SEQ/VAB
parser.  See the local `SEQ & Animation info page` reference.

## Implications for a host port

A first faithful host backend can retain the target's timing and data model:

1. decode and mix SPU-ADPCM from the WAVESET waveform region;
2. implement the known SMD interpreter and `MUS` channel state;
3. implement `feds`/SED effect streams and the driver voice allocator;
4. reproduce ADSR, pan, pitch modulation, noise, and reverb closely enough to
   validate against captured emulator output; and
5. only then replace the compatibility layer with a more ergonomic mixer if
   desired.

SDL can supply the output callback, but it does not replace the sequencer or
the SPU behavior.  A PSX-compatible audio core is therefore the lowest-risk
first backend.

## Evidence and open work

Local FFHacktics pages are external annotations and must be verified against
the USA target before their names or types are promoted into source:

- `Music/SMD` and `SUZUKI Read SMD Instructions`;
- `WAVESET.WD`, `SED`, `SCUS OpenGnrcSFX`, and `Put WAVESET.WD in SPU`;
- `SCUS MRTA OpenAndPlayMusic`, `SUZUKI PutPlaySMD`, and related Suzuki
  allocation/queue routines; and
- `Effect File Sounds` for the VFX `feds` pipeline.

High-value next steps are a read-only SMD/SED/WD inspector under `cmd/`, a
documented clean-room `MUS` and channel layout, and PCSX-Redux captures that
test one representative song, short jingle, UI SFX, looping ambience, and VFX
effect.  Those tests should settle the outstanding tempo, looping,
voice-stealing, and reverb questions without weakening any matching checks.

## The Suzuki region is not an excluded library range

`config/libraries.yaml` lists the Psy-Q ownership ranges, the lowest of which is
`LIBSPU` at `0x800186c4`. The Suzuki sequencer sits *below* that, roughly
`0x8001454c-0x800186c4`, and it is game/middleware code this project does
reconstruct -- `src/main/suzuki/` already holds matching functions such as
`SuzukiGetMusicPlaying` (`0x80012e7c`) and `SuzukiGetActiveChannels`
(`0x800135fc`).

Do not add that span to `libraries.yaml` and do not skip addresses inside it on
the grounds that it is "middleware". Two candidates (`0x800178e4`,
`0x800184e0`) were skipped that way and have been reinstated. AGENTS.md excludes
Sony library code; it does not exclude the game's own sound driver.

"No `jal` caller anywhere" is also weak evidence for skipping: the driver is
reached through function-pointer tables and from the timer callback, so a direct
call site need not exist.

