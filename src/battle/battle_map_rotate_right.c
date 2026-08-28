#include "psx/types.h"

extern s16 g_battle_camera_yaw;
extern s32 g_battle_previous_camera_yaw;
extern s32 g_battle_destination_camera_yaw;

void battle_map_rotate_right(s32 target_angle) {
    g_battle_previous_camera_yaw = g_battle_camera_yaw & 0xfe00;
    g_battle_destination_camera_yaw = target_angle;
    if ((target_angle & 0x3ff) == 0) {
        g_battle_destination_camera_yaw = target_angle - 0x200;
    }
}
