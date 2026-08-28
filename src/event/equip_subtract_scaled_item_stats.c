#include "psx/types.h"

void equip_subtract_scaled_item_stats(u8* arg0, u8* arg1, u8* arg2, s32 arg3) {
    *(s16*)(arg0 + 0x0) = *(u16*)(arg2 + 0x0) - (arg3 * *(s16*)(arg1 + 0x0));
    *(s16*)(arg0 + 0x2) = *(u16*)(arg2 + 0x2) - (arg3 * *(s16*)(arg1 + 0x2));
    *(s16*)(arg0 + 0x4) = *(u16*)(arg2 + 0x4) - (arg3 * *(s16*)(arg1 + 0x4));
    *(s16*)(arg0 + 0x6) = *(u16*)(arg2 + 0x6) - (arg3 * *(s16*)(arg1 + 0x6));
    *(s16*)(arg0 + 0x8) = *(u16*)(arg2 + 0x8) - (arg3 * *(s16*)(arg1 + 0x8));
    *(s16*)(arg0 + 0xa) = *(u16*)(arg2 + 0xa) - (arg3 * *(s16*)(arg1 + 0xa));
    *(s16*)(arg0 + 0xc) = *(u16*)(arg2 + 0xc) - (arg3 * *(s16*)(arg1 + 0xc));
    *(s16*)(arg0 + 0x12) = *(u16*)(arg2 + 0x12) - (arg3 * *(s16*)(arg1 + 0x12));
    *(s16*)(arg0 + 0x14) = *(u16*)(arg2 + 0x14) - (arg3 * *(s16*)(arg1 + 0x14));
    *(s16*)(arg0 + 0x16) = *(u16*)(arg2 + 0x16) - (arg3 * *(s16*)(arg1 + 0x16));
    *(s16*)(arg0 + 0x18) = *(u16*)(arg2 + 0x18) - (arg3 * *(s16*)(arg1 + 0x18));
    *(s16*)(arg0 + 0x1c) = *(u16*)(arg2 + 0x1c) - (arg3 * *(s16*)(arg1 + 0x1c));
    *(s16*)(arg0 + 0x1e) = *(u16*)(arg2 + 0x1e) - (arg3 * *(s16*)(arg1 + 0x1e));
    *(s16*)(arg0 + 0x20) = *(u16*)(arg2 + 0x20) - (arg3 * *(s16*)(arg1 + 0x20));
    *(s16*)(arg0 + 0x22) = *(u16*)(arg2 + 0x22) - (arg3 * *(s16*)(arg1 + 0x22));
}
