#include "psx/gpu.h"

extern void build_unit_battle_portrait_poly(POLY_FT4* poly, s32 portrait_id);

void bunit_build_portrait_poly_ft4(s32 portrait_id, POLY_FT4* poly) {
    if ((portrait_id & 0x300) == 0) {
        build_unit_battle_portrait_poly(poly, portrait_id);
    }
}
