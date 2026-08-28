#include "fft/battle.h"

extern battle_real_coords_t g_battle_offset_screen_coords;

battle_real_coords_t* battle_get_battle_offset_screen_coords(void) {
    return &g_battle_offset_screen_coords;
}
