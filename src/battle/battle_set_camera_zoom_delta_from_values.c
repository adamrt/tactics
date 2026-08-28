#include "fft/battle.h"

extern s32 g_animation_speed;
extern battle_real_coords_t g_battle_camera_zoom_delta;
extern u16 g_battle_camera_zoom_countdown;

void battle_set_camera_zoom_delta_from_values(const battle_real_coords_t* values,
    s32 frame_count) {
    s32 animation_frames;

    animation_frames = (frame_count & 0xffff) / g_animation_speed;
    g_battle_camera_zoom_countdown = animation_frames;
    animation_frames = g_battle_camera_zoom_countdown;
    g_battle_camera_zoom_delta.x = values->x / animation_frames;
    g_battle_camera_zoom_delta.z = values->z / animation_frames;
    g_battle_camera_zoom_delta.y = values->y / animation_frames;
}
