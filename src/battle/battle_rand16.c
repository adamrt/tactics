#include "psx/types.h"

extern s32 g_battle_rand16_state;

void battle_rand16(void) {
    g_battle_rand16_state = (g_battle_rand16_state * 0x6255 + 0x3619) & 0xFFFF;
}
