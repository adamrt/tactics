#include "fft/battle.h"

extern battle_misc_data_t* battle_get_mount_misc_data(battle_misc_data_t* unit);
extern s32 battle_calculate_screen_z_from_input_coords(battle_misc_data_t* unit,
    const s16* coords);

s32 battle_calculate_screen_z_with_caller_data(battle_misc_data_t* unit,
    const s16* coords) {
    battle_misc_data_t* mount;
    s32 adjusted_screen_z;
    s32 screen_z;

    mount = battle_get_mount_misc_data(unit);
    screen_z = battle_calculate_screen_z_from_input_coords(mount, coords);
    if (unit->mount_rider_value == 1) {
        adjusted_screen_z = screen_z - 10;
        screen_z = mount->mounted_height_offset + adjusted_screen_z;
    }
    return (s16)screen_z;
}
