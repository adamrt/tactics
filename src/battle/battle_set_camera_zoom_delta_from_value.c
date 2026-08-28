#include "fft/battle.h"

extern s32 g_animation_speed;
extern battle_real_coords_t g_battle_camera_zoom;
extern battle_real_coords_t g_battle_camera_zoom_delta;
extern u16 g_battle_camera_zoom_countdown;

void battle_set_camera_zoom_delta_from_value(const s32* destination_value,
    s32 frame_count) {
    s32 animation_frames;
    s32 delta_x;

    animation_frames = (frame_count & 0xffff) / g_animation_speed;
    delta_x = *destination_value - g_battle_camera_zoom.x;
    g_battle_camera_zoom_countdown = animation_frames;
    animation_frames = g_battle_camera_zoom_countdown;
    g_battle_camera_zoom_delta.x = delta_x / animation_frames;
    g_battle_camera_zoom_delta.z = (*destination_value - g_battle_camera_zoom.z) / animation_frames;
    g_battle_camera_zoom_delta.y = (*destination_value - g_battle_camera_zoom.y) / animation_frames;
}
