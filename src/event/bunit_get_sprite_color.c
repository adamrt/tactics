#include "psx/types.h"

extern u8 g_bunit_sprite_color[3];

u8* bunit_get_sprite_color(void) {
    return g_bunit_sprite_color;
}
