#include "psx/types.h"

s32 battle_effect_code_script_19(u8* effect) {
    s16 i;
    s32 count;
    u16 target;

    target = *(u16*)(*(s16*)(effect + 6) + *(s32*)(effect + 8) + 2);
    count = 0;
    for (i = 0; i < 4; i++) {
        if (((s16*)(effect + 0xC))[i] != 0) {
            count++;
        }
    }
    if ((s16)count == (s16)target) {
        *(s16*)(effect + 6) = *(u16*)(*(s16*)(effect + 6) + *(s32*)(effect + 8) + 4);
    } else {
        *(s16*)(effect + 6) += 6;
    }
    return 1;
}
