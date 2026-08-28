#include "psx/types.h"

extern u8* g_effect_data_ptrs[];
extern u8* g_effect_palette_data;
extern u8* g_effect_misc_data;

void battle_get_effect_misc_palette_addresses(s16 effect_id) {
    u8* effect_data;
    u8* effect_misc_data;

    effect_data = g_effect_data_ptrs[effect_id];
    effect_misc_data = effect_data + *(s32*)(effect_data + 0x1c);
    g_effect_misc_data = effect_misc_data;
    g_effect_palette_data = effect_misc_data + 8;
}
