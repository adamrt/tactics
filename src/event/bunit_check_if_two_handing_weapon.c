#include "psx/types.h"

extern u8 g_item_flags_by_id[];

s32 bunit_check_if_two_handing_weapon(s16* slots, s32 allow_secondary) {
    s32 ret = 0;
    s32 id = 0;

    if (slots[0] != 0) {
        if (slots[1] == 0) {
            id = slots[0] & 0x3FF;
        }
    } else if (slots[1] != 0) {
        id = slots[1] & 0x3FF;
    }
    if (id != 0 && id < 0x7A) {
        u8 flags = g_item_flags_by_id[id * 8];
        if (flags & 1) {
            ret = 1;
        } else if (allow_secondary != 0 && (flags & 4)) {
            ret = 1;
        }
    }
    return ret;
}
