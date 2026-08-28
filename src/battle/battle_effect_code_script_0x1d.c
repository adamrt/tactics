#include "psx/types.h"

extern u8* g_effect_palette_data;

s32 battle_effect_code_script_0x1d(u8* arg0) {
    if (*(s16*)(arg0 + 0x28) >= (s32) * (u16*)(g_effect_palette_data + 2)) {
        *(s16*)(arg0 + 6) = *(u16*)((s16) * (s16*)(arg0 + 6) + *(s32*)(arg0 + 8) + 2);
    } else {
        *(s16*)(arg0 + 6) = *(u16*)(arg0 + 6) + 4;
    }
    return 1;
}
