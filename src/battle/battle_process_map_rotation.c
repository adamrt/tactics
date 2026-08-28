#include "psx/types.h"

extern void main_play_sound_find_channel(s32 sound_id);
extern void main_stop_playing_sfx(s32 sound_id);
extern void battle_map_rotate_left(s32 angle);
extern s32 g_map_rotation_action;
extern s32 g_battle_game_state;
extern s16 g_battle_camera_yaw;
extern s32 g_battle_destination_camera_yaw;
extern s32 g_battle_map_rotation_increment;
extern s32 g_controller_input_previous;
extern s32 g_animation_speed;

void battle_process_map_rotation(void) {
    s32 angle;

    if (g_map_rotation_action == 1) {
        u16* yaw = (u16*)&g_battle_camera_yaw;
        *yaw -= g_battle_map_rotation_increment;
        if (g_battle_destination_camera_yaw < (s16)*yaw) {
            goto increment;
        }
        angle = (u16)g_battle_destination_camera_yaw & 0xFFF;
        *yaw = angle;
        if (g_controller_input_previous & 4) {
            if (g_battle_game_state != 0x34) {
                battle_map_rotate_left((angle & 0xFE0) - 0x400);
            }
            goto increment;
        }
    } else if (g_map_rotation_action == 2) {
        u16* yaw = (u16*)&g_battle_camera_yaw;
        *yaw += g_battle_map_rotation_increment;
        if ((s16)*yaw < g_battle_destination_camera_yaw) {
            goto increment;
        }
        angle = (u16)g_battle_destination_camera_yaw & 0xFFF;
        *yaw = angle;
        if (g_controller_input_previous & 8) {
            if (g_battle_game_state != 0x34) {
                battle_map_rotate_left((angle & 0xFE0) + 0x400);
            }
            goto increment;
        }
    } else {
        return;
    }
    g_map_rotation_action = 0;
    main_stop_playing_sfx(0xC);
    main_stop_playing_sfx(0xB);
    main_play_sound_find_channel(0xD);
increment:
    if (g_battle_map_rotation_increment < 0x30) {
        g_battle_map_rotation_increment = (g_animation_speed * 2) + g_battle_map_rotation_increment;
    }
}
