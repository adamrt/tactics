#include "psx/types.h"

extern u8 g_map_max_x;
extern u8 g_map_max_y;
extern u8 g_battle_tile_data[][8];
extern u8 targeting_panel_data[][5];

void battle_calculate_aoe_vertical_tolerance(s32 x, s32 y, s32 lo, s32 hi) {
    s32 level;
    s32 idx;
    s32 height;
    u8* tile;
    u8* panel;
    u32 flags;

    if ((x >= 0) && (x < g_map_max_x) && (y >= 0) && (y < g_map_max_y)) {
        level = 0;
        if (lo < 0) {
            lo = 0;
        }
        do {
            idx = (level << 8) + (y * g_map_max_x) + x;
            tile = g_battle_tile_data[idx];
            panel = targeting_panel_data[idx];
            flags = tile[3];
            height = (tile[2] * 2) + (flags & 0x1F) + ((flags >> 5) * 2);
            level++;
            if ((height >= lo) && (hi >= height)) {
                *panel = 1;
            }
        } while (level < 2);
    }
}
