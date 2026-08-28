#include "psx/types.h"

extern u32 g_selected_tile_x;
extern u32 g_selected_tile_elevation;
extern u32 g_selected_tile_y;
extern void main_set_svector(void* destination, u32 x, u32 elevation, u32 y);

void battle_store_selected_tile_coordinates(void* destination) {
    main_set_svector(destination, g_selected_tile_x, g_selected_tile_elevation, g_selected_tile_y);
}
