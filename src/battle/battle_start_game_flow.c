#include "psx/types.h"

extern s32 g_battle_game_flow_running;

void battle_start_game_flow(void) {
    g_battle_game_flow_running = 1;
}
