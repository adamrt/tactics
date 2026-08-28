# Final Fantasy Tactics decompilation

This is a matching decompilation of the North American PlayStation release of
*Final Fantasy Tactics* (`SCUS-94221`). Reconstructed C must compile to the same
bytes as the original game.

The project is incomplete. A build compiles the finished functions, checks
them against the original bytes, and combines them with the remaining original
game data. The resulting disc matches the original even though much of the game
has not been decompiled yet.

Game files and proprietary Sony tools are not included.

## Getting started

Install Docker and place your original raw Mode 2/2352 game BIN at the repository root:

```text
fft-us-scus-94221.bin
```

Then run:

```sh
make bootstrap
make build
```

`make bootstrap` builds the Docker image, checks the original BIN, extracts the
game files, creates an inventory, and runs the advisory PSX MIPS analysis pass.
Generated analysis reports are written under `build/analysis/inventory/`.
`make build` checks the project metadata, builds every reconstructed module, and
produces a byte-matching disc.

The required BIN size and hashes are in
[docs/target-disc.md](docs/target-disc.md).

## Common commands

```sh
make help                    # Show available commands
make doctor                  # Check the pinned Docker toolchain
make check-config            # Validate manifests and symbols
make build                   # Build every module and the disc
make build MODULE=battle     # Build one module
make test                    # Run tests for the Go tooling
make analyze                 # Re-run the extracted MIPS analysis pass
make run                     # Build, then launch PCSX-Redux
```

Module names are `main`, `battle`, `attack`, `card`, `debugchr`, `effect259`,
`equip`, `etc`, `helpmenu`, `jobstts`, `opening`, `option`, `require`, `bunit`,
`small`, `wldcore`, `world`, and `disc`.

PCSX-Redux runs on the host. On macOS the default path is
`/Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux`. Override it when
needed:

```sh
make run PCSX_REDUX=/path/to/pcsx-redux
```

## Development commands

These commands are optional and are not part of a normal build:

```sh
make compile-commands               # Create compile_commands.json for editors
make shell                          # Open a shell in the Docker image
```

WIP commands create and compare new function drafts. See
[docs/development.md](docs/development.md) for `draft`, `match`, `diff`,
`prepare`, and `permute` examples.

## Current state

`config/modules.yaml` is the machine-readable source of truth for matching
functions and byte ranges. Run `make check-config` for the current totals; the
single checked-in human-readable coverage snapshot is
[docs/reconstruction.md](docs/reconstruction.md).

The default compiler profile is GCC 2.6.3 with `-O2`, followed by ASPSX
2.34-compatible assembly. Individually proven exceptions are recorded on their
reconstructions in the manifest. Every registered function is checked against
the original machine code during the build.

The rebuilt disc matches the original BIN byte-for-byte. This proves the build
process preserves the disc; it does not mean the decompilation is complete.

## Repository layout

| Path | Purpose |
| --- | --- |
| `src/` | Matching C source |
| `wip/` | Unfinished C reconstructions and temporary linker scripts |
| `include/` | Project-owned declarations |
| `config/` | Module, symbol, and target metadata |
| `cmd/tools/` | Project tooling |
| `fft-us-scus-94221.bin` | Your ignored original game BIN |
| `build/` | Ignored extraction, build output, caches, and reports |

More detail is available in:

- [Reconstruction and coverage](docs/reconstruction.md)
- [Compiler toolchain](docs/compiler-toolchain.md)
- [Development workflow](docs/development.md)
- [Library ownership](docs/libraries.md)
- [Data structures](docs/data-structures.md)
- [Roadmap](ROADMAP.md)
