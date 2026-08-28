#include "psx/types.h"

extern s16 D_8018AAA6;

s32 world_get_menu_display_value_1(void) {
    s32 value = D_8018AAA6;
    if (value == 0) {
        return 0x20000000;
    }
    return value;
}
