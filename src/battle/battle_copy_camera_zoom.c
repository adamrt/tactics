#include "fft/battle.h"

extern battle_real_coords_t g_battle_camera_zoom;
extern battle_real_coords_t g_battle_camera_zoom_backup;

void battle_copy_camera_zoom(void) {
    g_battle_camera_zoom_backup.x = g_battle_camera_zoom.x;
    g_battle_camera_zoom_backup.z = g_battle_camera_zoom.z;
    g_battle_camera_zoom_backup.y = g_battle_camera_zoom.y;
}
