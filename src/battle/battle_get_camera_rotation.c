#include "psx/types.h"

extern u16 g_battle_camera_render_state[];

u16* battle_get_camera_rotation(void) {
    return g_battle_camera_render_state;
}
