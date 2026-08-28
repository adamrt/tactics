#include "psx/types.h"

extern u8* g_effect_parameter_sets_start;
extern u8* g_effect_parameter_sets;

void battle_reset_effect_parameter_sets_pointer(void) {
    g_effect_parameter_sets = g_effect_parameter_sets_start;
}
