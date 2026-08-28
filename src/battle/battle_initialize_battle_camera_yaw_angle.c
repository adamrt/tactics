#include "psx/types.h"

enum {
    BATTLE_CAMERA_YAW_WORD_INDEX = 0x1e,
};

extern u32* g_battle_script_variables;

void battle_initialize_battle_camera_yaw_angle(void) {
    g_battle_script_variables[BATTLE_CAMERA_YAW_WORD_INDEX] = (g_battle_script_variables[BATTLE_CAMERA_YAW_WORD_INDEX] + 0xa000)
        & 0x0fff;
}
