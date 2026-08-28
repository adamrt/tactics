#include "psx/types.h"

extern u16 g_battle_camera_render_state[];
extern u16 g_battle_camera_rotation_backup[];

void battle_copy_camera_rotation(void) {
    g_battle_camera_rotation_backup[0] = g_battle_camera_render_state[0];
    g_battle_camera_rotation_backup[1] = g_battle_camera_render_state[1];
    g_battle_camera_rotation_backup[2] = g_battle_camera_render_state[2];
}
