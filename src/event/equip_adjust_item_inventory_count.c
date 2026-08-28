#include "psx/types.h"

extern u8 g_player_inventory[];

/* EQUIP.OUT 001c684c - Add `delta` to the inventory count for the item id (low
 * 10 bits of `item`); clamped to 0. Item id 0 is a no-op sentinel. */
s32 equip_adjust_item_inventory_count(s32 item, s32 delta) {
    s32 item_id;
    s32 new_count;

    item_id = item & 0x3FF;
    if (item_id == 0) {
        return 0;
    }
    new_count = g_player_inventory[item_id] + delta;
    if (new_count < 0) {
        new_count = 0;
    }
    g_player_inventory[item_id] = new_count;
    return new_count;
}
