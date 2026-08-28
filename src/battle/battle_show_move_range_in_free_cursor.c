#include "fft/battle.h"
#include "psx/types.h"

extern void battle_start_game_flow(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void func_80174B8C(u8, u8, u8, u8);
extern void set_targeting_tile_background(s32, s32);
extern void main_play_sound(s32);
extern s32 g_battle_game_state;
extern s32 g_battle_controller_input;
extern s32 g_controller_input_copy_12;

void battle_show_move_range_in_free_cursor(void) {
    battle_misc_data_t* misc;
    battle_stats_t* stats;
    s32 prev;

    battle_start_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_DISPLAY_MOVE_AREA;
    misc = battle_get_casting_unit_misc_data();
    stats = misc->battle_data;
    func_80174B8C(stats->misc_unit_id, misc->map_x, misc->map_y, misc->map_z);
    set_targeting_tile_background(1, 1);
    prev = g_battle_controller_input;
    g_battle_controller_input = 2;
    g_controller_input_copy_12 = prev;
    main_play_sound(1);
}
