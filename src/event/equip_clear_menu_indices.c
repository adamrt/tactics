#include "psx/types.h"

extern s16 g_equip_menu_indices[4];

void equip_clear_menu_indices(void) {
    s32 i;

    for (i = 3; i >= 0; i--) {
        g_equip_menu_indices[i] = 0;
    }
}
