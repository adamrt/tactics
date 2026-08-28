#include "psx/types.h"

extern s32 g_world_main_menu_scroll_direction;
extern s32 g_world_main_menu_scroll_threshold;

void world_set_main_menu_scroll_parameters(s32 direction, s32 threshold) {
    g_world_main_menu_scroll_direction = direction;
    g_world_main_menu_scroll_threshold = threshold;
}
