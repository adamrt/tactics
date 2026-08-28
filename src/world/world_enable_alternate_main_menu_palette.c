#include "psx/types.h"

extern s32 g_world_use_alternate_main_menu_palette;

void world_enable_alternate_main_menu_palette(void) {
    g_world_use_alternate_main_menu_palette = 1;
}
