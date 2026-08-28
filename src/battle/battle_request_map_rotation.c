#include "psx/types.h"

extern void battle_call_map_rotate_left(s32 angle);
extern void battle_call_map_rotate_right(s32 angle);
extern void main_play_sound_find_channel(s32 sound_id);
extern s32 g_map_rotation_action;
extern s16 g_battle_camera_yaw;

void battle_request_map_rotation(s32 angle) {
    if (g_map_rotation_action == 0) {
        if (angle < 0) {
            battle_call_map_rotate_left((g_battle_camera_yaw & 0xFE00) + angle);
            main_play_sound_find_channel(0xB);
        } else {
            battle_call_map_rotate_right((g_battle_camera_yaw & 0xFE00) + angle);
            main_play_sound_find_channel(0xC);
        }
    }
}
