#include "psx/types.h"

extern volatile u8 g_battle_tile_data[];

void battle_disable_green_panel_flags(void) {
    s32 i;
    volatile u8* p;
    i = 0;
    p = g_battle_tile_data;
    do {
        i++;
        p[5] &= 0x7F;
        p += 8;
    } while (i < 0x200);
}
