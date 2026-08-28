# EFFECT overlay evidence

The USA disc contains `EFFECT/E000.BIN` through `E511.BIN`. A review of every
target file against the local FFHacktics snapshot classifies 110 files as
native MIPS plus effect data and 402 as data-only. The review covers all 268
indexed E-number routine pages and records 209 target-checked native ranges and
32 groups of byte-identical code. Generated review material belongs under
`build/analysis/effect-wiki/`; `config/modules.yaml` remains authoritative for
accepted matching C.

## Effect identities and names

FFHacktics page `00006760.wiki` maps E-numbers to effect names and asset
metadata. In a slash-separated label, the left side is the PSX name used by
this project and the right side is the PSP localization alias. For example,
`Regen/Regenerator` establishes canonical PSX name `Regen`. The PSP alias is
provenance, not a source-symbol name. When a row has more than one slash, the
first component remains the canonical PSX name.

Overlay-specific reconstructed symbols use both identities:

```text
effect_e456_flood_update_specialized_map_destruction_state
```

The numeric ID stays visible because it is the stable disc identity; the PSX
name makes browsing readable. A helper proven byte-identical across unrelated
effects instead receives one behavior-based name. The individual module
records carry each E-number and effect name, avoiding a false implication that
shared engine logic belongs to one particular spell.

An effect name alone does not establish a routine's behavior. Semantic suffixes
come from the target instructions, callers, globals, and routine-specific wiki
pages. Unknown command meanings remain numeric until stronger evidence exists.

## Range corrections

Target return instructions and adjacent data establish four useful corrections
to broad wiki mappings:

- E080's adjacent routines meet at `0x801c463c`; `0x801c4638` is the first
  routine's return delay-slot `nop`, not the second routine's entry.
- E451's second native function is `0x801c3af8–0x801c50c8`.
- E464's function on page 9874 is `0x801c4b54–0x801c4dc4`; later mapped bytes
  are data.
- E480's freeze handler is `0x801c42d8–0x801c436c`; later mapped bytes are data.

The first-word heuristic is advisory only. E259, E338, and E464 contain native
code despite not beginning with the usual negative-stack-frame instruction.
