#include "psx/types.h"

extern void* g_battle_scratch_pad_ptr;

void battle_spread_move_to_east_preset(void) {
    void* p = g_battle_scratch_pad_ptr;
    *(s16*)((u8*)p + 0x3A) = 1;
    *(s16*)((u8*)p + 0x3C) = 0;
    *(s8*)((u8*)p + 0x44) = 0;
    *(s8*)((u8*)p + 0x45) = 2;
}
