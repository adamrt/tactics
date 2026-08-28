#include "fft/battle.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32 x, s32 y, s32 z);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void store_unit_names_and_event_block_data(s32 a, u8 b, s32 c);
extern void system_function_setup(s32 a, s32 b, u8 c, s32 d, s32 e);
extern s32 g_battle_game_state;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

void battle_target_select_confirm(void) {
    battle_misc_data_t* misc;
    battle_stats_t* stats;

    battle_stop_game_flow();
    g_battle_game_state = 0x22;
    misc = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
    if (misc != 0) {
        stats = misc->battle_data;
        if (stats != 0) {
            store_unit_names_and_event_block_data(3, stats->misc_unit_id, 0);
        }
    }
    stats = battle_get_casting_unit_misc_data()->battle_data;
    system_function_setup(9, 0, stats->misc_unit_id, 0, 1);
}
