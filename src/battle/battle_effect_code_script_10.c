#include "psx/types.h"

s32 battle_effect_code_script_10(u8* ctx) {
    u8* cur;
    u32 slot;

    cur = (u8*)(*(s16*)(ctx + 6) + *(s32*)(ctx + 8));
    slot = (u32)cur[1] >> 6;
    *(u16*)(ctx + slot * 2 + 0x14) = *(u16*)(cur + 2);
    *(s16*)(ctx + 6) = *(u16*)(ctx + 6) + 4;
    return 1;
}
