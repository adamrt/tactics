#include "psx/types.h"
typedef void (*EffFn)(s16, u32, s32, s32);
extern EffFn battle_get_effect_file_pointer(s16);
s32 battle_effect_code_script_07(u8* effect) {
    u8* p = (u8*)(*(s16*)(effect + 6) + *(s32*)(effect + 8));
    u32 k = *(u8*)(p + 1) >> 2;
    EffFn f = battle_get_effect_file_pointer(*(s16*)(p + 2));
    *(EffFn*)(effect + 0xF4) = f;
    f(*(s16*)(effect + 2), k, 0, 0);
    *(s16*)(effect + 6) += 4;
    return 1;
}
