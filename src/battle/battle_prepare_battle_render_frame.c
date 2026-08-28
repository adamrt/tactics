#include "psx/gte.h"

extern u16 g_battle_gfx_counter;
extern u16 g_battle_previous_gfx_counter;

void battle_prepare_battle_render_frame(void) {
    SetGeomOffset(0, 0);
    g_battle_previous_gfx_counter = g_battle_gfx_counter;
}
