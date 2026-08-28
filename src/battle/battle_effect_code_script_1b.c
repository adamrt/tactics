#include "psx/types.h"

s32 battle_effect_code_script_1b(u8* ctx) {
    u8* cur;
    u32 slot;

    cur = (u8*)(*(s16*)(ctx + 6) + *(s32*)(ctx + 8));
    slot = (u32)cur[1] >> 4;
    if (*(s16*)(ctx + slot * 2 + 0xC) == 0) {
        *(s16*)(ctx + 6) = *(u16*)(cur + 2);
    } else {
        *(s16*)(ctx + 6) = *(s16*)(ctx + 6) + 4;
    }
    return 1;
}
