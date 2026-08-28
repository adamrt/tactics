#include "psx/types.h"

s32 battle_effect_code_script_14(u8* ctx) {
    s16 pc = *(s16*)(ctx + 6);
    u8* cur = (u8*)(pc + *(s32*)(ctx + 8));
    s16* counter = &((s16*)(ctx + 0x14))[(u32)cur[1] >> 6];
    if (*counter <= *(s16*)(cur + 2)) {
        *(s16*)(ctx + 6) = (s16) * (u16*)(cur + 4);
    } else {
        *(s16*)(ctx + 6) = pc + 6;
    }
    return 1;
}
