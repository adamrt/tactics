#include "fft/battle.h"

extern battle_real_coords_t g_battle_current_real_coords;
extern battle_real_coords_t g_battle_real_coord_delta;
extern u16 g_battle_real_coord_countdown;

void battle_tick_real_coord_animation(void) {
    if (g_battle_real_coord_countdown != 0) {
        g_battle_real_coord_countdown--;
        g_battle_current_real_coords.x += g_battle_real_coord_delta.x;
        g_battle_current_real_coords.z += g_battle_real_coord_delta.z;
        g_battle_current_real_coords.y += g_battle_real_coord_delta.y;
    }
}
