#include "psx/types.h"

extern void func_8018370C(void* buf, s32 arg1);

s32 battle_calculate_at_list_and_get_specific_unit_id(s32 unit_idx) {
    u8 buf[0xA0];
    u32 entry;
    u32 lo;

    func_8018370C(buf, 0);
    entry = buf[unit_idx * 4];
    lo = entry & 0x1F;
    if (lo == 0x1F) {
        return -4;
    }
    if (entry & 0x40) {
        lo += 0x100;
    }
    return lo;
}
