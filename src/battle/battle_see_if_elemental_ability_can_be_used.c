#include "psx/types.h"

extern u8 g_ai_map_max_x;
extern u8 g_battle_tile_data[];
extern s16 D_8019F3C6;
extern u8 g_geomancy_terrain_ability_table[];

s32 battle_see_if_elemental_ability_can_be_used(u8* coords) {
    u32 tile_id;
    u32 tile_type;
    u32 ability_terrain;

    tile_id = (coords[1] << 8) + coords[2] * g_ai_map_max_x + coords[0];
    tile_type = g_battle_tile_data[tile_id * 8] & 0x3F;
    ability_terrain = g_geomancy_terrain_ability_table[tile_type];
    return (ability_terrain ^ D_8019F3C6) < 1;
}
