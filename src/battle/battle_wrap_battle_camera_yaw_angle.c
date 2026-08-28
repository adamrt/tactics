#include "psx/types.h"

enum {
    BATTLE_CAMERA_YAW_WORD_INDEX = 0x1e,
    FULL_CAMERA_TURN = 0x1000,
};

extern s32* g_battle_script_variables;

s32 battle_wrap_battle_camera_yaw_angle(void) {
    s32 yaw;

    yaw = g_battle_script_variables[BATTLE_CAMERA_YAW_WORD_INDEX];
    while (yaw < 0) {
        yaw += FULL_CAMERA_TURN;
    }
    return yaw;
}
