#include "fft/battle.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);
extern void battle_decide_facing_direction(battle_misc_data_t* unit, s32 facing);
extern void set_rider_mount_map_position(u8 misc_id, u8 map_x, u8 map_y,
    u8 map_z, u8 facing_index);
extern s32 func_8019ABB4(void);
extern s32 g_battle_game_state;
extern s32 g_current_facing_direction;

void battle_choose_facing_for_wait(void) {
    battle_misc_data_t* mounted_unit;
    battle_misc_data_t* unit;
    s32 facing;

    battle_stop_game_flow();
    unit = battle_get_source_unit_misc_data();
    facing = *(s16*)&unit->facing;
    g_battle_game_state = 0x13;
    g_current_facing_direction = facing;
    unit->unit_check = 0;
    if (unit->mount_rider_value == 1) {
        mounted_unit = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (mounted_unit != 0) {
            battle_decide_facing_direction(
                unit, *(s16*)&mounted_unit->facing);
            if (unit->battle_data != 0) {
                set_rider_mount_map_position(
                    unit->battle_data->misc_unit_id, unit->map_x, unit->map_y,
                    unit->map_z,
                    (u8)(*(s16*)&mounted_unit->facing / 0x400));
            }
        }
    }
    if ((unit->team_flags & 8) == 0) {
        unit->facing_hint = func_8019ABB4();
    }
}
