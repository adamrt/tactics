#include "psx/types.h"

extern u8 g_battle_map_max_x;
extern u8 g_battle_map_max_y;
extern u8 g_battle_tile_data[0x1000];

extern void* memcpy(void*, const void*, u32);

void battle_copy_xy_coords_and_map_tile_data(u8* p) {
    g_battle_map_max_x = *p++;
    g_battle_map_max_y = *p++;
    memcpy(g_battle_tile_data, p, 0x1000);
}
