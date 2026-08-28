#include "psx/types.h"

extern s32 g_battle_current_vector_x;
extern s32 g_battle_current_vector_z;
extern s32 g_battle_current_vector_y;
extern s32 g_map_rotation_action;
extern s32 g_battle_map_tilt_action;
extern s32 g_battle_map_zoom_action;

s32 battle_is_battle_camera_active(void) {
    /* Pin: unpinned, GCC builds the result in $v1 and adds a trailing
     * `move v0,v1` (128 bytes); early-return and split-if forms do the same. */
    register s32 result asm("$2");

    result = 1;
    if (g_battle_current_vector_x == 0 && g_battle_current_vector_z == 0 && g_battle_current_vector_y == 0 && g_map_rotation_action == 0 && g_battle_map_tilt_action == 0) {
        result = g_battle_map_zoom_action != 0;
    }

    return result;
}
