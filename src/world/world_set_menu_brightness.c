#include "psx/types.h"

extern s32 g_world_menu_color_red;
extern s32 g_world_menu_color_green;
extern s32 g_world_menu_color_blue;

void world_set_menu_brightness(s32 red, s32 green, s32 blue) {
    g_world_menu_color_red = red;
    g_world_menu_color_green = green;
    g_world_menu_color_blue = blue;
}
