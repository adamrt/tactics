#include "psx/types.h"

extern u8 g_bunit_sprite_color[3];

void bunit_set_sprite_color(const u8* color) {
    if (color != 0) {
        g_bunit_sprite_color[0] = color[0];
        g_bunit_sprite_color[1] = color[1];
        g_bunit_sprite_color[2] = color[2];
    }
}
