#include "psx/types.h"

extern u8 g_move_find_item_flags[];

s32 battle_move_find_item_flag_calculation(s32 arg0, s32 arg1, s32 arg2) {
    s32 idx;
    s32 bit;

    idx = arg0 / 2;
    bit = 0x80 >> (((arg0 & 1) * 4) + arg1);
    if (arg2 == 0) {
        return (g_move_find_item_flags[idx] & bit) == 0;
    }
    g_move_find_item_flags[idx] = (u8)bit | g_move_find_item_flags[idx];
    return 1;
}
