#include "psx/gpu.h"

extern u8 g_equip_item_type_icon_coords[][2];

void equip_get_item_type_icon_rect(s32 index, RECT* output) {
    output->x = g_equip_item_type_icon_coords[index][0];
    output->y = g_equip_item_type_icon_coords[index][1];
    output->w = 12;
    output->h = 12;
}
