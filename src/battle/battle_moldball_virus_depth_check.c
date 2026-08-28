#include "psx/types.h"

extern u8 targeting_panel_data[];
extern u8 g_battle_tile_data[];

void battle_moldball_virus_depth_check(s16 arg0) {
    u8* p;
    u8* q;
    s32 i;

    if (arg0 != 0x149)
        return;
    i = 0;
    q = targeting_panel_data;
    p = g_battle_tile_data;
    do {
        if (p[3] & 0xE0) {
            *q = 0;
        }
        p += 8;
        i += 1;
        q += 5;
    } while (i < 0x200);
}
