#include "psx/types.h"

extern u8 g_inventory[];

s32 world_change_item_quantity_on_equip(s32 item_id, s32 delta) {
    s32 idx;
    s32 v;

    idx = item_id & 0x3FF;
    v = 0;
    if (idx != 0) {
        v = g_inventory[idx] + delta;
        if (v < 0) {
            v = 0;
        }
        g_inventory[idx] = (u8)v;
    }
    return v;
}
