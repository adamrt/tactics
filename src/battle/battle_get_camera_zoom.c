#include "fft/battle.h"

extern battle_real_coords_t g_battle_camera_zoom;

battle_real_coords_t* battle_get_camera_zoom(void) {
    return &g_battle_camera_zoom;
}
