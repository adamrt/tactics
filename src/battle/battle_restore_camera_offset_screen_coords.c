#include "fft/battle.h"

extern battle_real_coords_t g_battle_offset_screen_coords;
extern battle_real_coords_t g_battle_camera_offset_screen_coords;

void battle_restore_camera_offset_screen_coords(void) {
    g_battle_offset_screen_coords.x = g_battle_camera_offset_screen_coords.x;
    g_battle_offset_screen_coords.z = g_battle_camera_offset_screen_coords.z;
    g_battle_offset_screen_coords.y = g_battle_camera_offset_screen_coords.y;
}
