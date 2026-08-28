#include "psx/types.h"

s32 battle_effect_code_script_17(u8* arg0) {
    s16 pc = *(s16*)(arg0 + 6);
    s16* pos = (s16*)(pc + *(s32*)(arg0 + 8));
    if (pos[1] < *(s16*)(arg0 + 0x1C)) {
        *(s16*)(arg0 + 6) = (s16) * (u16*)(pos + 2);
    } else {
        *(s16*)(arg0 + 6) = pc + 6;
    }
    return 1;
}
