#include "psx/types.h"

extern u8 g_equip_sprite_color;
extern u8 g_equip_sprite_color_g;
extern u8 g_equip_sprite_color_b;
extern u8 g_equip_compact_layout;

/* Stream command: set the sprite RGB; the compact layout uses the second
   colour triple of the command. */
u8* equip_parse_set_sprite_color(u8* cmd) {
    u8 blue;
    if (g_equip_compact_layout != 0) {
        g_equip_sprite_color = cmd[5];
        g_equip_sprite_color_g = cmd[6];
        blue = cmd[7];
    } else {
        g_equip_sprite_color = cmd[2];
        g_equip_sprite_color_g = cmd[3];
        blue = cmd[4];
    }
    g_equip_sprite_color_b = blue;
    return cmd + cmd[1];
}
