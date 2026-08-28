#include "psx/types.h"

extern u8 g_equip_item_inventory_totals[];

u8 equip_get_item_total_count(s32 arg0) {
    return g_equip_item_inventory_totals[arg0 & 0x3FF];
}
