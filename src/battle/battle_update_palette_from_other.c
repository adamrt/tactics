#include "psx/types.h"

extern void modify_vram_palette(s32 mode, const u16* source, s32 section_id,
    s32 unit_misc_id, s32 preset, s16 red,
    s16 green, s16 blue, s32 final_value);

void battle_update_palette_from_other(const u16* source, s32 section_id,
    s32 unit_misc_id, s32 preset, s16 red,
    s16 green, s16 blue, s32 final_value) {
    modify_vram_palette(8, source, section_id, unit_misc_id, preset, red, green,
        blue, final_value);
}
