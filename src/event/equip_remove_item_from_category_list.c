#include "psx/types.h"

extern u8* g_equip_item_category_lists[];

/* Remove the first occurrence of `value` from the 0xFF-terminated byte list. */
void equip_remove_item_from_category_list(s32 value, s32 index) {
    u8* list = g_equip_item_category_lists[index];
    s32 i;

    for (i = 0; list[i] != value; i++) {
        if (list[i] == 0xFF) {
            return;
        }
    }

    do {
        list[i] = list[i + 1];
        i++;
    } while (list[i] != 0xFF);
}
