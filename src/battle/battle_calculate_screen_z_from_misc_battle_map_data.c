#include "fft/battle.h"
#include "psx/types.h"

typedef struct BattleCoordShort {
    s16 x;
    s16 z;
    s16 y;
    s16 pad;
} BattleCoordShort;

extern battle_misc_data_t* battle_get_mount_misc_data(battle_misc_data_t* unit);
extern s32 battle_calculate_screen_z_from_input_coords(
    battle_misc_data_t* unit, const BattleCoordShort* coords);

s32 battle_calculate_screen_z_from_misc_battle_map_data(battle_misc_data_t* unit) {
    BattleCoordShort coord;
    battle_stats_t* battle_data;
    battle_misc_data_t* mount;
    s32 adjusted_screen_z;
    s32 screen_z;

    mount = battle_get_mount_misc_data(unit);
    battle_data = mount->battle_data;
    coord.x = battle_data->x * 0x1c + 0xe;
    battle_data = mount->battle_data;
    coord.y = battle_data->position.bits.y * 0x1c + 0xe;
    coord.z = mount->map_z;
    screen_z = battle_calculate_screen_z_from_input_coords(mount, &coord);
    if (unit->mount_rider_value == 1) {
        adjusted_screen_z = screen_z - 10;
        screen_z = mount->mounted_height_offset + adjusted_screen_z;
    }
    return (s16)screen_z;
}
