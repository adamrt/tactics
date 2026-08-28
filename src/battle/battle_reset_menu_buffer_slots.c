#include "psx/types.h"

extern s32 g_battle_menu_buffer_slots[6];

/* Mark all three menu-buffer pointer pairs as unallocated. */
void battle_reset_menu_buffer_slots(void) {
    s32 value = -1;
    s32 index = 5;
    s32* slot = &g_battle_menu_buffer_slots[5];

    do {
        *slot = value;
        index -= 1;
        slot -= 1;
    } while (index >= 0);
}
