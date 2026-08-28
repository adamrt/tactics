#include "psx/types.h"

extern s32 g_effect_phase;

void battle_play_effect(void) {
    if (g_effect_phase == 1) {
        g_effect_phase = 2;
    }
}
