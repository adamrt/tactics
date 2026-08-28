#include "psx/types.h"

s32 battle_effect_code_script_1c(u8* ctx) {
    u8* cur;
    u32 slot;
    s16 pc;

    pc = *(s16*)(ctx + 6);
    cur = (u8*)(pc + *(s32*)(ctx + 8));
    slot = (u32)cur[1] >> 6;
    if (*(s16*)(ctx + slot * 2 + 0x14) != *(s16*)(cur + 2)) {
        *(s16*)(ctx + 6) = *(u16*)(cur + 4);
    } else {
        *(s16*)(ctx + 6) = pc + 6;
    }
    return 1;
}
