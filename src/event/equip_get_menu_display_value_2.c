#include "psx/types.h"

extern s16 g_equip_menu_value_2;

s32 equip_get_menu_display_value_2(void) {
    s32 value = g_equip_menu_value_2;

    if (value == 0) {
        return 0x20000000;
    }
    return value;
}
