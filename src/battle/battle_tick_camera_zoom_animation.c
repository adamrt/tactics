#include "fft/battle.h"

extern battle_real_coords_t g_battle_camera_zoom;
extern battle_real_coords_t g_battle_camera_zoom_delta;
extern u16 g_battle_camera_zoom_countdown;

void battle_tick_camera_zoom_animation(void) {
    if (g_battle_camera_zoom_countdown != 0) {
        g_battle_camera_zoom_countdown--;
        g_battle_camera_zoom.x += g_battle_camera_zoom_delta.x;
        g_battle_camera_zoom.z += g_battle_camera_zoom_delta.z;
        g_battle_camera_zoom.y += g_battle_camera_zoom_delta.y;
    }
}
