#include "psx/types.h"

extern u8* g_effect_data_ptrs[];
extern u8* g_effect_nibble_table;

void battle_set_effect_nibble_table_pointer(s16 effect_id) {
    u8* effect_data;

    effect_data = g_effect_data_ptrs[effect_id];
    g_effect_nibble_table = effect_data + *(s32*)(effect_data + 0x14);
}
