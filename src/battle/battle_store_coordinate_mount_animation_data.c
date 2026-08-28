#include "fft/battle.h"
#include "psx/types.h"

extern void func_8017FDDC(u8, u8, u8, u8, u8);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8);
extern void battle_set_move_and_screen_coords(battle_misc_data_t*);
extern void battle_calculate_screen_z_from_misc_screen_data(battle_misc_data_t*);
extern void battle_move_cursor_to_unit(battle_misc_data_t*);
extern void func_80082EEC(battle_misc_data_t*);

void battle_store_coordinate_mount_animation_data(battle_misc_data_t* unit) {
    battle_stats_t* data;
    battle_misc_data_t* mount;

    data = unit->battle_data;
    if (data != 0) {
        /* facing is read signed (lh) here. */
        func_8017FDDC(data->misc_unit_id, unit->map_x, unit->map_y, unit->map_z,
            *(s16*)&unit->facing / 1024);
        if (unit->mount_rider_value != 0) {
            mount = battle_get_unit_misc_data_by_misc_id(unit->unit_id);
            if (unit->battle_data != 0) {
                func_8017FDDC(mount->battle_data->misc_unit_id, unit->map_x,
                    unit->map_y, unit->map_z,
                    *(s16*)&unit->facing / 1024);
            }
        }
    }
    battle_set_move_and_screen_coords(unit);
    battle_calculate_screen_z_from_misc_screen_data(unit);
    battle_move_cursor_to_unit(unit);
    unit->movement_path_count = 0;
    func_80082EEC(unit);
}
