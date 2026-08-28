#include "fft/data.h"

extern s16 g_world_fitting_room_items[][5];
extern s32 world_change_item_quantity_on_equip(s32 item_id, s32 delta);

void world_buy_from_fitting_room(void) {
    s32 i;
    s32 j;

    for (i = 0; i < g_world_formation_unit_count; i++) {
        for (j = 0; j < 5; j++) {
            s32 item = g_world_formation_unit_pointers[i]->equipment[j];
            if ((item >> 14) != 0) {
                g_world_formation_unit_pointers[i]->equipment[j] &= WORLD_ITEM_ID_MASK;
            }
            world_change_item_quantity_on_equip(g_world_fitting_room_items[i][j], 1);
            g_world_fitting_room_items[i][j] = 0;
        }
    }
}
