#include "psx/types.h"

s32 equip_out_get_item_type_from_item_number(s32 item) {
    s32 result;

    item &= 0x3FF;
    result = 0;
    if (item >= 0x7A) {
        result = 5;
        if (item >= 0x80) {
            result = 1;
            if (item >= 0x90) {
                result = 2;
                if (item >= 0xAC) {
                    if (item < 0xD0) {
                        result = 3;
                    } else {
                        result = 5;
                        if (item < 0xF0) {
                            result = 4;
                        }
                    }
                }
            }
        }
    }
    return result;
}
