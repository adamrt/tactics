#include "psx/types.h"

extern s32 g_effect_phase;

void battle_set_effect_phase_none(void) {
    if (g_effect_phase == 1) {
        g_effect_phase = 0;
    }
}
