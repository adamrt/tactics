#include "psx/types.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_sp2_data;

void battle_finish_hiding_unit_status(void) {
    g_animation_speed = 1;
    g_battle_game_state = 0x2A;
    g_sp2_data = 0;
}
