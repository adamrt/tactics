#include "psx/types.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_map_transition_step;
extern s32 g_game_flow_state;

void battle_half_animation_speed_and_queue_close(s32 arg0, s32 arg1) {
    g_animation_speed = 2;
    g_battle_game_state = 0x3B;
    g_map_transition_step = arg0;
    g_game_flow_state = arg1;
}
