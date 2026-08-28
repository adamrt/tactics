#include "psx/types.h"

extern u8 g_map_max_x;
extern u8 g_map_max_y;
extern u8 g_battle_tile_data[];

u8* battle_get_tile_data_pointer(s32 x, s32 y, u32 layer) {
    s32 max_x = g_map_max_x;
    s32 max_y = g_map_max_y;
    if (x < 0 || x >= max_x || y < 0 || y >= max_y || layer >= 2U) {
        return 0;
    }
    return &g_battle_tile_data[((layer << 8) + y * max_x + x) * 8];
}
