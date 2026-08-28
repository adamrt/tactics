#include "psx/types.h"

extern u8 g_battle_palette_update_flags[];
extern void battle_palette_modification(
    s32 first,
    s32 second,
    s32 third,
    s32 palette_index,
    s32 fifth,
    s32 sixth,
    s32 seventh,
    s32 eighth);

void battle_update_unit_palettes(void) {
    s32 palette_index = 0;
    s32 flag_offset = 0;

    while (palette_index < 0x10) {
        if (g_battle_palette_update_flags[flag_offset] != 0) {
            battle_palette_modification(10, 4, 3, palette_index, 0, 0, 0, 0);
            battle_palette_modification(8, 4, 3, palette_index, 0, 0, 0, 0);
        }
        palette_index++;
        flag_offset += 8;
    }
}
