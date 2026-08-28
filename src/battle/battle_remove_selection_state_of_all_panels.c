#include "psx/types.h"

extern volatile u8 g_battle_tile_data[];
extern u8 targeting_panel_data[];

s32 battle_remove_selection_state_of_all_panels(void) {
    s32 count;
    s32 i;
    s32 no_tile;
    volatile u8* src;
    u8* dst;

    count = 0;
    i = 0;
    no_tile = 0x3F;
    src = g_battle_tile_data;
    dst = targeting_panel_data;
    do {
        if (dst[1] != 0 && !(src[6] & 1) && (src[0] & 0x3F) != no_tile) {
            count++;
            src[5] |= 0x40;
        } else {
            src[5] &= 0xBF;
        }
        src += 8;
        i++;
        dst += 5;
    } while (i < 0x200);
    return count;
}
