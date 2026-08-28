#include "psx/types.h"

extern u32 g_world_formation_menu_entry_mask;

void world_set_formation_menu_entry_mask(u32 mask) {
    g_world_formation_menu_entry_mask = mask;
}
