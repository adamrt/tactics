#include "psx/types.h"

enum {
    EQUIP_ITEM_LIST_ENTRY_ITEM_ID_MASK = 0x3ff,
    EQUIP_ITEM_LIST_ENTRY_EQUIPPED = 0x4000,
    EQUIP_ITEM_AVAILABILITY_EQUIPPED = 0x40000000,
};

extern u16 g_equip_item_list_entries[];
extern s32 equip_get_item_available_count(s32 arg0);

/* EQUIP.OUT 001c4180 - Look up menu-row slot `row`, get its item-available
 * count, and merge the "already-equipped" flag into the availability value. */
s32 equip_get_item_avail_with_equip_flag(s32 row) {
    u16 entry = g_equip_item_list_entries[row];
    s32 result = equip_get_item_available_count(entry & EQUIP_ITEM_LIST_ENTRY_ITEM_ID_MASK);
    if (g_equip_item_list_entries[row] & EQUIP_ITEM_LIST_ENTRY_EQUIPPED) {
        result |= EQUIP_ITEM_AVAILABILITY_EQUIPPED;
    }
    return result;
}
