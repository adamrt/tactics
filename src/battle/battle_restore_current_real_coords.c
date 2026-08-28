#include "fft/battle.h"

extern battle_real_coords_t g_battle_current_real_coords;
extern battle_real_coords_t g_battle_saved_real_coords;

void battle_restore_current_real_coords(void) {
    g_battle_current_real_coords.x = g_battle_saved_real_coords.x;
    g_battle_current_real_coords.z = g_battle_saved_real_coords.z;
    g_battle_current_real_coords.y = g_battle_saved_real_coords.y;
}
