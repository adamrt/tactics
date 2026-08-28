#include "fft/battle.h"

extern s32 g_battle_game_state;
extern s32 g_selected_tile_x;
extern s32 g_selected_tile_y;
extern s32 g_selected_tile_elevation;

void battle_stop_game_flow(void);
battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
battle_misc_data_t* battle_get_casting_unit_misc_data(void);
void battle_store_unit_names_and_some_event_block_data(s32, s32, s32);
void battle_system_function_setup_routine(s32, s32, s32, s32, s32);

void battle_target_select_denied(void) {
    battle_misc_data_t* misc;
    battle_misc_data_t* unit;
    battle_stats_t* stats;
    s32 kind;

    battle_stop_game_flow();
    g_battle_game_state = 0x21;
    misc = battle_get_misc_data_at_map_coords_2(g_selected_tile_x, g_selected_tile_y,
        g_selected_tile_elevation);
    if (misc != 0) {
        stats = misc->battle_data;
        if (stats != 0) {
            battle_store_unit_names_and_some_event_block_data(3, stats->misc_unit_id, 0);
        }
    }
    unit = battle_get_casting_unit_misc_data();
    if (misc == 0) {
        battle_system_function_setup_routine(9, 3, unit->battle_data->misc_unit_id, 0, 1);
        return;
    }
    /* 0x1b6: undocumented byte before status_change_count. */
    kind = *((u8*)unit + 0x1B6);
    if (kind == 0xC) {
        battle_system_function_setup_routine(9, 1, unit->battle_data->misc_unit_id, 0, 1);
        return;
    }
    if (kind == 0xE) {
        battle_system_function_setup_routine(9, 2, unit->battle_data->misc_unit_id, 0, 1);
    }
}
