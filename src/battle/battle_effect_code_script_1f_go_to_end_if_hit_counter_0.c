#include "psx/types.h"

extern u16 g_effect_coord_data;

s32 battle_effect_code_script_1f_go_to_end_if_hit_counter_0(u8* arg0) {
    s16 pc = *(s16*)(arg0 + 6);
    s32 base = *(s32*)(arg0 + 8);
    u8* ptr = (u8*)(pc + base);
    if (g_effect_coord_data == ((u32)ptr[1] >> 2)) {
        *(s16*)(arg0 + 6) = *(u16*)(ptr + 2);
    } else {
        *(s16*)(arg0 + 6) = pc + 4;
    }
    return 1;
}
