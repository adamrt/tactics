#include "psx/types.h"

extern u8 g_equip_sprite_color[3];

u8* equip_get_sprite_color(void) {
    return g_equip_sprite_color;
}
