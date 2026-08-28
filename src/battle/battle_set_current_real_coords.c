#include "fft/battle.h"

extern battle_real_coords_t g_battle_current_real_coords;

void battle_set_current_real_coords(const battle_real_coords_t* coords) {
    g_battle_current_real_coords.x = coords->x;
    g_battle_current_real_coords.z = coords->z;
    g_battle_current_real_coords.y = coords->y;
}
