#include "psx/types.h"

extern s32 g_effect_inertia_threshold;
extern s32 g_saved_effect_inertia_threshold;

void battle_save_effect_inertia_threshold(void) {
    g_saved_effect_inertia_threshold = g_effect_inertia_threshold;
}
