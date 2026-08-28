#include "fft/battle.h"

extern battle_real_coords_t g_battle_current_real_coords;

battle_real_coords_t* battle_get_current_real_coords(void) {
    return &g_battle_current_real_coords;
}
