#include "psx/types.h"

extern void main_play_sound(s32 sound_id);
extern s32 g_battle_map_tilt_action;
extern s32 g_battle_map_tilt_target;
extern s16 g_battle_camera_render_state;
extern s32 g_battle_map_tilt_increment;

void battle_process_map_tilt_request(s32 mode) {
    switch (mode) {
    case 0:
        if (g_battle_camera_render_state >= 0x12F) {
            g_battle_map_tilt_target = 1;
            g_battle_map_tilt_action = 4;
            g_battle_map_tilt_increment = 1;
            main_play_sound(0x31);
        } else if (g_battle_camera_render_state < 0x12E) {
            g_battle_map_tilt_target = 1;
            g_battle_map_tilt_action = 2;
            g_battle_map_tilt_increment = 1;
            main_play_sound(0x31);
        }
        break;
    case 1:
        if (g_battle_camera_render_state >= 0x1C1) {
            g_battle_map_tilt_target = 2;
            g_battle_map_tilt_action = 4;
            g_battle_map_tilt_increment = mode;
            main_play_sound(0x31);
        } else if (g_battle_camera_render_state < 0x1C0) {
            g_battle_map_tilt_action = 2;
            g_battle_map_tilt_target = 2;
            g_battle_map_tilt_increment = mode;
            main_play_sound(0x31);
        }
        break;
    }
}
