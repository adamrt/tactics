#include "psx/types.h"

extern u8* g_effect_misc_data;
extern u16 g_effect_coord_data;

s32 battle_effect_code_script_1e_check_all_timing_bytes(u8* arg0) {
    u8* m;

    m = g_effect_misc_data;
    if (*(s16*)(arg0 + 0x28) >= (s32)(*(u16*)(m + 4) + *(u16*)(m + 2) + (g_effect_coord_data - 1) * *(u16*)(m + 6) + *(u16*)(m + 0xA))) {
        *(s16*)(arg0 + 6) = *(u16*)(*(s16*)(arg0 + 6) + *(s32*)(arg0 + 8) + 2);
    } else {
        *(s16*)(arg0 + 6) += 4;
    }
    return 1;
}
