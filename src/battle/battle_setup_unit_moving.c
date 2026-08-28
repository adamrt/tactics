#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_game_state;
extern s32 g_shifted_controller_flags;
extern s32 g_selected_tile_x;
extern s32 g_selected_tile_y;
extern s32 g_selected_tile_elevation;

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_3(s32 x, s32 y, s32 z);
extern void battle_system_function_setup_routine(s32 a, s32 b, s32 c, s32 d, s32 e);

void battle_setup_unit_moving(void) {
    battle_misc_data_t* src;
    battle_misc_data_t* cast;
    battle_misc_data_t* at_tile;
    u8 v;

    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_UNIT_MOVING_SETUP;
    src = battle_get_source_unit_misc_data();
    cast = battle_get_casting_unit_misc_data();

    if (cast->mount_byte & 0x80) {
        battle_system_function_setup_routine(2, 1, src->battle_data->misc_unit_id,
            0, src->team_flags & 8);
        return;
    }
    v = cast->movement_path_count + 2;
    if (v < 2) {
        if (g_shifted_controller_flags & 0x18000) {
            battle_system_function_setup_routine(2, 0, src->battle_data->misc_unit_id,
                0, src->team_flags & 8);
            return;
        }
        battle_system_function_setup_routine(0xD, 0, src->battle_data->misc_unit_id,
            0, src->team_flags & 8);
        return;
    }
    at_tile = battle_get_misc_data_at_map_coords_3(g_selected_tile_x, g_selected_tile_y,
        g_selected_tile_elevation);
    if (at_tile != 0) {
        if (at_tile->status_flags_5_6 & 1) {
            battle_system_function_setup_routine(2, 4, src->battle_data->misc_unit_id,
                0, src->team_flags & 8);
            return;
        }
    }
    battle_system_function_setup_routine(2, 0, src->battle_data->misc_unit_id, 0,
        src->team_flags & 8);
}
