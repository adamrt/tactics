#include "psx/types.h"

extern u8 g_map_max_x;
extern u8 g_map_max_y;
extern u8 targeting_panel_data[][5];

void battle_remove_close_range_routine(s32 x, s32 y, s32 range) {
    s32 i;
    s32 j;
    s32 dy;
    s32 dx;
    s32 k;

    for (i = 0; i < g_map_max_y; i++) {
        dy = (y < i) ? (i - y) : (y - i);
        for (j = 0; j < g_map_max_x; j++) {
            dx = (x < j) ? (j - x) : (x - j);
            if (range >= (dy + dx)) {
                targeting_panel_data[(i * g_map_max_x) + j][0] = 0;
                k = j + 0x100;
                targeting_panel_data[(i * g_map_max_x) + k][0] = 0;
            }
        }
    }
}
