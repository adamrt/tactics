#include "psx/types.h"

extern u8 g_bunit_sprite_color;
extern u8 g_bunit_sprite_color_g;
extern u8 g_bunit_sprite_color_b;
extern u8 D_801EC8F4;

/* Set the sprite RGB from the command; D_801EC8F4 selects the second
 * (offset +3) colour triple. */
u8* bunit_parse_set_sprite_color(u8* data) {
    u8 blue;
    if (D_801EC8F4 != 0) {
        g_bunit_sprite_color = data[5];
        g_bunit_sprite_color_g = data[6];
        blue = data[7];
    } else {
        g_bunit_sprite_color = data[2];
        g_bunit_sprite_color_g = data[3];
        blue = data[4];
    }
    g_bunit_sprite_color_b = blue;
    return data + data[1];
}
