#include "fft/battle.h"

extern battle_real_coords_t g_battle_offset_screen_coords;

void battle_set_battle_offset_screen_coords(battle_real_coords_t* coords) {
    g_battle_offset_screen_coords.x = coords->x;
    g_battle_offset_screen_coords.z = coords->z;
    g_battle_offset_screen_coords.y = coords->y;
}
