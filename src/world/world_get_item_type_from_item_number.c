#include "psx/types.h"

s32 world_get_item_type_from_item_number(s32 item_id) {
    s32 type;

    item_id &= 0x3FF;
    type = 0;
    if (item_id < 0x7A)
        goto ret;
    type = 5;
    if (item_id < 0x80)
        goto ret;
    type = 1;
    if (item_id < 0x90)
        goto ret;
    type = 2;
    if (item_id < 0xAC)
        goto ret;
    if (item_id < 0xD0) {
        type = 3;
        goto ret;
    }
    if (item_id < 0xF0) {
        type = 4;
        goto ret;
    }
    type = 5;
ret:
    return type;
}
