#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;

void battle_half_animation_speed_for_jump_in(void) {
    g_animation_speed = 2;
    g_battle_game_state = BATTLE_GAME_STATE_MAP_JUMPING_IN;
}
