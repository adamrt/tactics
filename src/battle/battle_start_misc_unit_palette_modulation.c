#include "psx/types.h"

enum {
    MISC_UNIT_SLOT_COUNT = 16,
};

extern void battle_apply_misc_unit_palette_modulation(
    s32 preset_color, s32 time, s32 misc_id,
    s32 red, s32 green, s32 blue);

void battle_start_misc_unit_palette_modulation(
    s32 preset_color, s32 time, s32 misc_id,
    s16 red, s16 green, s16 blue) {
    s32 index;

    if (misc_id >= MISC_UNIT_SLOT_COUNT) {
        for (index = 0; index < MISC_UNIT_SLOT_COUNT; index++) {
            battle_apply_misc_unit_palette_modulation(
                preset_color, time, index, red, green, blue);
        }
    } else {
        battle_apply_misc_unit_palette_modulation(
            preset_color, time, misc_id, red, green, blue);
    }
}
