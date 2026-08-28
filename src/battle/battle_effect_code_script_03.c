#include "psx/types.h"

extern void func_801A1D9C(s16);

s32 battle_effect_code_script_03(u8* effect) {
    s32 o = (*(u8*)(*(s16*)(effect + 6) + *(s32*)(effect + 8) + 1) >> 3) & 6;
    s16 a = ((s16*)(effect + 0xC))[o >> 1];
    if (a != 0)
        func_801A1D9C(a);
    *(u16*)(effect + 6) += 2;
    return 1;
}
