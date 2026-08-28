#include "psx/types.h"

extern u16 g_battle_camera_render_state[];

void battle_set_camera_rotation(const u16* rotation) {
    g_battle_camera_render_state[0] = rotation[0];
    g_battle_camera_render_state[1] = rotation[1];
    g_battle_camera_render_state[2] = rotation[2];
}
