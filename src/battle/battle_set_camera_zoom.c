#include "fft/battle.h"

extern battle_real_coords_t g_battle_camera_zoom;

void battle_set_camera_zoom(const battle_real_coords_t* zoom) {
    g_battle_camera_zoom.x = zoom->x;
    g_battle_camera_zoom.z = zoom->z;
    g_battle_camera_zoom.y = zoom->y;
}
