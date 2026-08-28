#include "fft/battle.h"

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern s32 func_8017FFC0(battle_stats_t*);
extern void func_80071EE8(void);
extern void battle_clear_at_list_active(void);
extern s32 g_battle_move_find_result;
extern s32 g_post_action_display_phase;
extern s32 g_animation_continue_check;

void battle_post_movement_display_prep(void) {
    battle_stats_t* stats;

    battle_stop_game_flow();
    stats = battle_get_casting_unit_misc_data()->battle_data;
    if (stats != 0) {
        g_battle_move_find_result = func_8017FFC0(stats);
    } else {
        g_battle_move_find_result = 0;
    }
    g_post_action_display_phase = 0;
    func_80071EE8();
    if (g_battle_move_find_result != 0) {
        battle_clear_at_list_active();
    }
    g_animation_continue_check = 0;
}
