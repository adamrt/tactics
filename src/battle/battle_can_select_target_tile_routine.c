#include "psx/types.h"

extern s8 targeting_panel_data[];
extern u8 g_battle_tile_data[];

void battle_can_select_target_tile_routine(void) {
    s32 i = 0;
    s8* dst = targeting_panel_data;
    u8* src = g_battle_tile_data;
    for (; i < 0x200; i++) {
        if (src[6] & 2)
            *dst = 0;
        src += 8;
        dst += 5;
    }
}
