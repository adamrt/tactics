#include "psx/types.h"

extern u8 g_map_max_x;
extern u8 g_map_max_y;
extern void main_set_svector(void* destination, u32 x, u32 elevation, u32 y);

void battle_store_map_max_coordinates(void* destination) {
    main_set_svector(destination, g_map_max_x, 0, g_map_max_y);
}
