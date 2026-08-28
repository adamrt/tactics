#include "psx/types.h"

extern void configure_misc_unit_palette_modulation(
    s32 misc_id, s32 mode, s16 red, s16 green, s16 blue);

void battle_prepare_misc_unit_palette_modulation(s32 misc_id, s32 mode, s16 red,
    s16 green, s16 blue) {
    configure_misc_unit_palette_modulation(misc_id, mode, red, green, blue);
}
