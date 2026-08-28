#include "psx/types.h"

extern s16 D_8018AAAC;

s32 world_get_menu_display_value_2(void) {
    s32 value = D_8018AAAC;
    if (value == 0) {
        return 0x20000000;
    }
    return value;
}
