#include "psx/types.h"

extern s32 battle_map_location_calculation(void);
extern u8 g_battle_tile_data[];
extern u8 g_geomancy_terrain_ability_table[];

u8 battle_get_elemental_ability_id(void) {
    return g_geomancy_terrain_ability_table[g_battle_tile_data[battle_map_location_calculation() * 8] & 0x3F];
}
