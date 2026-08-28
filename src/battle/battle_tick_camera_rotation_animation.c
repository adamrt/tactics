#include "psx/types.h"

extern u16 g_battle_camera_render_state[];
extern u16 g_battle_camera_rotation_delta[];
extern u16 g_battle_camera_rotation_countdown;

void battle_tick_camera_rotation_animation(void) {
    if (g_battle_camera_rotation_countdown != 0) {
        g_battle_camera_rotation_countdown--;
        g_battle_camera_render_state[0] += g_battle_camera_rotation_delta[0];
        g_battle_camera_render_state[1] += g_battle_camera_rotation_delta[1];
        g_battle_camera_render_state[2] += g_battle_camera_rotation_delta[2];
    }
}
