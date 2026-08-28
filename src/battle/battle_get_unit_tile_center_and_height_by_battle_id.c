#include "fft/battle.h"

typedef struct BattleTileCenterAndHeight {
    s16 x;
    s16 z;
    s16 y;
} BattleTileCenterAndHeight;

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);
extern void* get_tile_data_ptr(u32 x, u32 y, u32 elevation);
extern s32 battle_calculate_screen_z_from_misc_battle_map_data(
    battle_misc_data_t* unit);

s32 battle_get_unit_tile_center_and_height_by_battle_id(
    u32 battle_id, BattleTileCenterAndHeight* coords) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_battle_id(battle_id & 0xffff);
    if (unit != 0) {
        get_tile_data_ptr(unit->battle_data->x,
            unit->battle_data->position.bits.y,
            unit->battle_data->position.raw >> 15);
        coords->x = unit->battle_data->x * 28 + 14;
        coords->y = unit->battle_data->position.bits.y * 28 + 14;
        coords->z = battle_calculate_screen_z_from_misc_battle_map_data(unit);
        return 1;
    }
    return 0;
}
