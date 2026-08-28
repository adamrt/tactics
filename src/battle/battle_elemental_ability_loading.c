#include "psx/types.h"

extern u8* battle_get_existent_battle_unit_pointer(s32 unit_id);
extern s32 battle_map_location_calculation(u8* unit);
extern s32 func_801817C0(s32 a0, u8 a1, s16* a2, void* a3, void* sp10, s32 sp14, void* sp18, void* sp1c);
extern u8 g_battle_tile_data[];
extern u8 g_geomancy_terrain_ability_table[];

s32 battle_elemental_ability_loading(s32 unit_id, u8 ability) {
    u8* unit;
    s16 targets[0x14];
    u8 sp48[0x18];
    u8 sp60[0x18];
    u8 sp78[0x18];
    u8 sp90[0x18];
    s32 count;
    s32 i;
    s16 element;

    unit = battle_get_existent_battle_unit_pointer(unit_id);
    if (unit == 0) {
        return 0;
    }
    if (ability != 0x11) {
        return 0;
    }
    count = func_801817C0(unit_id, 0x11, targets, sp48, sp60, 1, sp78, sp90);
    if (count == 0) {
        return 0;
    }
    element = g_geomancy_terrain_ability_table[g_battle_tile_data[battle_map_location_calculation(unit) * 8] & 0x3F];
    for (i = 0; i < count; i++) {
        if (targets[i] == element) {
            return (u16)element;
        }
    }
    return 0;
}
