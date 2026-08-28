#include "psx/types.h"

extern s16 g_world_menu_draw_priority;

void world_set_menu_draw_priority(s16 priority) {
    g_world_menu_draw_priority = priority;
}
