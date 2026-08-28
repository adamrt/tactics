#include "psx/types.h"

extern void configure_misc_unit_palette_modulation(s32 unit_id, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void battle_configure_misc_unit_palette_modulation_1f(s32 unit_id) {
    configure_misc_unit_palette_modulation(unit_id, 4, 0x1F, 0, 0);
}
