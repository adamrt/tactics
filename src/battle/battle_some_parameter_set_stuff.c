#include "psx/types.h"

extern u8* g_effect_parameter_sets;

void battle_some_parameter_set_stuff(u8* ctx, s32 arg1, s32 arg2) {
    u8* base;
    u8* p;
    s32 word;
    u16 flags;

    base = g_effect_parameter_sets;
    p = (u8*)(((arg2 << 16) >> 15) + (s32)base);
    flags = *(u16*)(ctx + 6) | 1;
    word = p[0] + (p[1] << 8);
    *(s16*)(ctx + 0x1C) = 0;
    *(s8*)(ctx + 0x1E) = (s8)((arg1 & 0xFF) * 2);
    *(s16*)(ctx + 0x16) = 0;
    *(u16*)(ctx + 6) = flags;
    *(s32*)(ctx + 0x18) = (s32)(s16)word + (s32)base;
}
