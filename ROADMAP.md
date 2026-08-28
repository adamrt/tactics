# Roadmap

The end goal is a readable, matching reconstruction of the supported FFT disc.
Work should stay byte-exact and reproducible as coverage grows.

## Next

- [ ] Prefer compact, documented Square/game routines and overlays where a
      complete executable code range is realistically attainable; use remaining
      mapped-code size rather than raw file size to choose completion targets.
- [ ] Continue larger modules in parallel without weakening each module's
      independent exact-byte build.
- [ ] Expand shared game data declarations only when exact functions establish
      a field, record size, or table stride.

## Build-system growth

- [ ] Preserve or infer original translation-unit boundaries only where they
      demonstrably affect code generation or layout.

## Reverse engineering

- [ ] Revisit clean near-matches only when a source-level explanation for the
      remaining compiler shape is available.
- [ ] Confirm the `EVENT/SMALL.OUT` load address dynamically in PCSX-Redux
      (its complete static code range already matches in C).
- [ ] Expand call-graph, data-reference, and overlay-loading analysis.
- [ ] Replace provisional `func_` and `D_` names only when behavior or data
      structure provides defensible evidence.
- [ ] Revisit the locked compiler profile only when a function cannot match it
      and focused evidence identifies a concrete toolchain difference.
- [ ] Continue `BATTLE.BIN` from its verified `0x80067000` raw-overlay address
      model while establishing equivalent models for other overlays.

## Later

- [ ] Replace extracted data inclusions with understood, reviewable source
      representations.
- [ ] Rebuild complete translation units and modules rather than splicing
      individual matching ranges.
- [ ] Define project-wide progress and completion criteria for the supported
      disc version.
