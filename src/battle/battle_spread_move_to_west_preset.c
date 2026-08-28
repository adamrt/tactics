#include "psx/types.h"

extern u8* g_battle_scratch_pad_ptr;

void battle_spread_move_to_west_preset(void) {
    u8* p = g_battle_scratch_pad_ptr;
    *(s16*)(p + 0x3A) = -1;
    *(s16*)(p + 0x3C) = 0;
    *(s8*)(p + 0x44) = 2;
    *(s8*)(p + 0x45) = 0;
}
