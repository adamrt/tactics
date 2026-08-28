#include "psx/types.h"

extern s16 g_equip_menu_indices[4];

s32 equip_set_menu_index_1(s32 index, s32 value) {
    g_equip_menu_indices[(u8)index] = value;
    return (s16)value;
}
