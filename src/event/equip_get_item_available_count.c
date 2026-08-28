#include "psx/types.h"

extern s32 equip_adjust_item_inventory_count(s32, s32);
extern u8 g_equip_item_inventory_totals[];

/* EQUIP.OUT 001c8188 - Number of copies of item id `item` still unequipped:
 * total owned (g_equip_item_inventory_totals) minus currently equipped (0-delta trick). */
s32 equip_get_item_available_count(s32 item) {
    s32 item_id;

    item_id = item & 0x3FF;
    return g_equip_item_inventory_totals[item_id] - equip_adjust_item_inventory_count(item_id, 0);
}
