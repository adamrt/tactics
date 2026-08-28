#include "psx/types.h"

extern u16 g_world_draw_suppress_flag;

void world_set_draw_suppress_flag(void) {
    g_world_draw_suppress_flag = 1;
}
