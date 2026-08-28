#include "fft/battle.h"

extern s32 g_battle_game_state;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_y;
extern s32 g_battle_cursor_z;

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
extern void battle_system_function_setup_routine(s32, s32, s32, s32, s32);

void battle_confirm_action(void) {
    battle_misc_data_t* unit;
    battle_misc_data_t* target;
    s32 mode;

    battle_stop_game_flow();
    g_battle_game_state = 0x1B;
    unit = battle_get_source_unit_misc_data();
    target = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y,
        g_battle_cursor_z);
    switch (unit->ability_preview_phase) {
    case 0:
        if (target != 0) {
            battle_system_function_setup_routine(4, 1, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        } else {
            battle_system_function_setup_routine(4, 2, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        }
        break;
    case 1:
        if (target != 0) {
            battle_system_function_setup_routine(4, 4, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        } else {
            battle_system_function_setup_routine(4, 2, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        }
        break;
    case 2:
        if (target != 0) {
            battle_system_function_setup_routine(4, 3, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        } else {
            battle_system_function_setup_routine(4, 2, unit->battle_data->misc_unit_id, 0,
                unit->team_flags & 8);
        }
        break;
    default:
        battle_system_function_setup_routine(4, 0, unit->battle_data->misc_unit_id, 0,
            unit->team_flags & 8);
        break;
    }
}
