#include "psx/types.h"

extern u8 g_item_flags_by_id[];

typedef struct {
    s16 slot_a;
    s16 slot_b;
} WeaponPair;

s32 equip_check_if_two_handing_weapon(WeaponPair* slots, s32 two_hands_support) {
    s32 result;
    s32 item_id;
    s16 w0;
    s16 w1;
    u8 flags;

    result = 0;
    w0 = slots->slot_a;
    item_id = 0;
    if (w0 != 0) {
        if (slots->slot_b == 0) {
            item_id = w0;
        }
    } else {
        w1 = slots->slot_b;
        if (w1 != 0) {
            item_id = w1;
        }
    }
    if (item_id != 0 && item_id < 0x7A) {
        flags = g_item_flags_by_id[item_id * 8];
        if (flags & 1) {
            result = 1;
        } else if (two_hands_support != 0) {
            if (flags & 4) {
                result = 1;
            }
        }
    }
    return result;
}
