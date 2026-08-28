# Linked PlayStation libraries

`SCUS_942.21` statically links Sony PlayStation support code. The reviewed
ownership ranges are stored in `config/libraries.yaml`:

| Range | Ownership |
| --- | --- |
| `0x800186c4–0x8001bb5b` | Psy-Q `LIBSPU` |
| `0x8001bb5c–0x8001dacf` | Psy-Q `LIBGTE` |
| `0x8001dad0–0x8001e8c3` | Psy-Q `LIBETC` |
| `0x8001e8c4–0x8002228b` | Psy-Q `LIBCD` |
| `0x8002228c–0x80022c23` | C runtime |
| `0x80022c24–0x800275bf` | Psy-Q `LIBGPU` |
| `0x800275c0–0x80028acb` | Psy-Q `LIBCARD` |

These boundaries are supported by the FFHacktics routine map and the target's
contiguous routine layout. Square's SUZUKI sound layer is not classified as
`LIBSPU`: it is separate game or middleware code that calls the Sony library.

## Version evidence

Reviewed long signatures identify Psy-Q 3.5 versions of
`LIBCD.LIB/BIOS.OBJ`, `LIBGPU.LIB/PRIM.OBJ`, and `LIBGPU.LIB/SYS.OBJ`. Their
offsets and signature lengths are recorded in `libraries.yaml`. This identifies
those objects; it does not prove that every linked library object came from
exactly the same SDK release. The one-time signature scanner is not retained as
production tooling.

## Reviewed symbols and headers

Library entry points are promoted to `config/main-symbols.yaml` only
when their target address, behavior, and external identity agree. Each reviewed
library symbol declares its owning range, which the build validates.

Project-owned clean-room ABI declarations live under `include/psx/`, including
the focused GPU, GTE, ETC, CD, SPU, and C-runtime interfaces required so far. They cover
only the types and calls currently needed by matching C. Compile-time checks
enforce the target sizes of `RECT`, `DR_ENV`, `DRAWENV`, `DISPENV`, `TIM_IMAGE`,
`POLY_F4`, and `DR_MODE`. No proprietary Psy-Q headers or libraries are required
or stored.

Recognized library bytes are reported separately from reconstructed FFT game
code. The current build reconstructs 25 contiguous `LIBGPU/PRIM.OBJ` packet
helpers (596 bytes) and 11 SUZUKI sound-middleware routines (140 bytes). The
remaining linked-library routines can stay as external calls while new matching
work focuses on Square's game code.
