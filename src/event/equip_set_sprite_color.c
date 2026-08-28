#include "psx/types.h"

extern u8 g_equip_sprite_color[3];

void equip_set_sprite_color(const u8* data) {
    g_equip_sprite_color[0] = data[0];
    g_equip_sprite_color[1] = data[1];
    g_equip_sprite_color[2] = data[2];
}
