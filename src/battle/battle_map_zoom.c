#include "psx/types.h"

extern s32 g_battle_camera_zoom;
extern s32 g_battle_map_zoom_target;
extern s32 g_battle_map_zoom_action;
extern s32 g_battle_map_zoom_increment;

extern void main_play_sound(s32 id);

void battle_map_zoom(s32 mode) {
    switch (mode) {
    case 0:
        if (g_battle_camera_zoom > 0x1000) {
            g_battle_map_zoom_target = 1;
            g_battle_map_zoom_action = 4;
            g_battle_map_zoom_increment = 4;
            main_play_sound(0x11);
            return;
        }
        if (g_battle_camera_zoom < 0x1000) {
            g_battle_map_zoom_target = 1;
            g_battle_map_zoom_action = 2;
            g_battle_map_zoom_increment = 4;
            main_play_sound(0xE);
            return;
        }
        return;
    case 1:
        if (g_battle_camera_zoom > 0xC00) {
            g_battle_map_zoom_target = 4;
            g_battle_map_zoom_action = 4;
            g_battle_map_zoom_increment = 4;
            main_play_sound(0x11);
            return;
        }
        if (g_battle_camera_zoom < 0xC00) {
            g_battle_map_zoom_target = 4;
            g_battle_map_zoom_action = 2;
            g_battle_map_zoom_increment = 4;
            main_play_sound(0xE);
            return;
        }
        return;
    }
}
