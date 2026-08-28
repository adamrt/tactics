#include "psx/types.h"

extern s32 g_effect_inertia_threshold;

void battle_set_effect_inertia_threshold(s32 threshold) {
    g_effect_inertia_threshold = threshold;
}
