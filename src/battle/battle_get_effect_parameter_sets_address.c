#include "psx/types.h"

extern u8* g_effect_data_ptrs[];
extern u8* g_effect_parameter_sets;

void battle_get_effect_parameter_sets_address(s16 effect_id) {
    u8* effect_data;

    effect_data = g_effect_data_ptrs[effect_id];
    g_effect_parameter_sets = effect_data + *(s32*)(effect_data + 0x4) + 4;
}
