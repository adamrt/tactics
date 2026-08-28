#include "psx/types.h"

extern u8 g_battle_tile_data[];
extern s8 targeting_panel_data[];

void battle_clear_some_stuff_for_untargetable_terrain(void) {
    s32 i;
    u8* src;
    s8* dst;

    i = 0;
    dst = targeting_panel_data;
    src = g_battle_tile_data;
    do {
        if (src[6] & 2) {
            dst[0] = 0;
            dst[1] = 0;
        }
        src += 8;
        i += 1;
        dst += 5;
    } while (i < 0x100);
}
