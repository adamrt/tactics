#include "psx/types.h"

extern void build_unit_battle_portrait_poly(void* poly, s32 portrait_id);

void equip_build_portrait_poly_if_valid(s32 portrait_id, void* poly) {
    if ((portrait_id & 0x300) == 0) {
        build_unit_battle_portrait_poly(poly, portrait_id);
    }
}
