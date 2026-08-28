#include "psx/types.h"

extern u8* g_effect_nibble_table;

s32 battle_lookup_effect_animation_timing_curve_value(void* entry) {
    u16 packed_index;
    s32 offset;
    s32 packed_value;

    packed_index = *(u16*)((u8*)entry + 0x28);
    offset = (s16)packed_index / 2;
    packed_value = g_effect_nibble_table[(u32)(offset + 0x12c)];
    if (packed_index & 1) {
        packed_value >>= 4;
    }
    return packed_value & 0xf;
}
