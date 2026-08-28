#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_post_action;
extern void* get_acting_unit_misc_data(void);
extern void battle_move_cursor_to_unit(void*);
extern void system_function_setup(s32, s32, s32, s32, s32);

void battle_set_state_after_command(void) {
    g_animation_speed = 1;
    g_battle_game_state = BATTLE_GAME_STATE_AFTER_COMMAND;
    g_post_action = 0;
    battle_move_cursor_to_unit(get_acting_unit_misc_data());
    system_function_setup(6, 0, 0, 0, 0);
}
