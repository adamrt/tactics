#include "psx/types.h"

extern s32 battle_get_effect_file_pointer(s16);
extern s32 D_801B9144[];

s32 battle_effect_code_script_06(u16* effect) {
    u8* p = (u8*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4));
    u32 idx = (u32)p[1] >> 2;
    D_801B9144[idx] = battle_get_effect_file_pointer(*(s16*)(p + 2));
    effect[3] += 4;
    return 1;
}
