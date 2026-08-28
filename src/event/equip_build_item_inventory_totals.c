#include "psx/types.h"

extern void bcopy(void* src, void* dst, s32 n);
extern u8* main_get_party_data_pointer(s32 index);

extern u8 g_player_inventory[];
extern u8 g_equip_item_inventory_totals[];

/* Snapshot the player inventory counts, then add every item currently equipped
   by the 20 party roster slots. */
void equip_build_item_inventory_totals(void) {
    s32 i;
    s32 j;
    u8* unit;
    u32 item;

    bcopy(g_player_inventory, g_equip_item_inventory_totals, 0x100);

    for (i = 0; i < 20; i++) {
        unit = main_get_party_data_pointer(i);
        if (unit[1] != 0xFF) {
            for (j = 0; j < 7; j++) {
                item = (unit + j)[0xE];
                if (item != 0 && item < 0xFE) {
                    g_equip_item_inventory_totals[item]++;
                }
            }
        }
    }
}
