#include "psx/gpu.h"

extern void build_unit_battle_portrait_poly(POLY_FT4* poly, s32 portrait_id);
extern void func_801c8c08(POLY_FT4* poly, s32 portrait_id);

void attack_build_portrait_poly_ft4(s32 portrait_id, POLY_FT4* poly) {
    if ((portrait_id & 0x300) == 0) {
        build_unit_battle_portrait_poly(poly, portrait_id);
    }
    if ((portrait_id & 0x200) != 0) {
        func_801c8c08(poly, portrait_id & 0xff);
    }
}
