#include "psx/types.h"

s32 battle_effect_code_script_15(u8* arg0) {
    s16 pc = *(s16*)(arg0 + 6);
    u8* script = (u8*)(pc + *(s32*)(arg0 + 8));
    if (*(s16*)(arg0 + 0x14 + ((script[1] >> 6) * 2)) < *(s16*)(script + 2)) {
        *(s16*)(arg0 + 6) = (s16) * (u16*)(script + 4);
    } else {
        *(s16*)(arg0 + 6) = pc + 6;
    }
    return 1;
}
