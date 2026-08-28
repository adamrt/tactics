#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_map_transition_step;
extern s32 g_game_flow_state;

void battle_begin_close_battle(s32 duration) {
    g_animation_speed = 2;
    g_battle_game_state = BATTLE_GAME_STATE_CLOSE_BATTLE;
    g_map_transition_step = duration != 0 ? 0x100 / duration : 0x100;
    g_game_flow_state = 1;
}
