#include "psx/types.h"

extern u8 targeting_panel_data[];
extern u8 g_battle_map_max_x;
extern u8 g_battle_map_max_y;

void battle_linear_attack_tile_calculation(s32 dir, s32 x, s32 y) {
    s32 i;
    s32 dx;
    s32 dy;
    s32 w;
    u8* p;

    switch (dir) {
    case 0:
        dx = 1;
        dy = 0;
        break;
    case 2:
        dx = -1;
        dy = 0;
        break;
    case 6:
        dx = 0;
        dy = 1;
        break;
    case 4:
        dx = 0;
        dy = -1;
        break;
    default:
        return;
    }

    i = 0;
    do {
        if (x < 0) {
            return;
        }
        w = g_battle_map_max_x;
        if (x >= w) {
            return;
        }
        if (y < 0) {
            return;
        }
        if (y >= (s32)g_battle_map_max_y) {
            return;
        }
        dir = y * w + x;
        p = &targeting_panel_data[dir * 5];
        if (p[0] != 0) {
            p[1] = 1;
        }
        dir += 0x100;
        p = &targeting_panel_data[dir * 5];
        y += dy;
        if (p[0] != 0) {
            p[1] = 1;
        }
        i += 1;
        x += dx;
    } while (i < 0x20);
}
