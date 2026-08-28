#include "fft/battle.h"

extern s32 g_animation_speed;
extern battle_real_coords_t g_battle_offset_screen_coords;
extern battle_real_coords_t g_battle_offset_screen_coords_fixed;
extern battle_real_coords_t g_battle_real_coord_delta;
extern u16 g_battle_offset_screen_coord_countdown;

void battle_set_offset_screen_coord_delta_from_values(
    const battle_real_coords_t* values, s32 frame_count) {
    s32 animation_frames;

    animation_frames = (frame_count & 0xffff) / g_animation_speed;
    g_battle_offset_screen_coords_fixed.x = g_battle_offset_screen_coords.x << 12;
    g_battle_offset_screen_coords_fixed.z = g_battle_offset_screen_coords.z << 12;
    g_battle_offset_screen_coords_fixed.y = g_battle_offset_screen_coords.y << 12;
    g_battle_offset_screen_coord_countdown = animation_frames;
    animation_frames = g_battle_offset_screen_coord_countdown;
    g_battle_real_coord_delta.x = (values->x << 12) / animation_frames;
    g_battle_real_coord_delta.z = (values->z << 12) / animation_frames;
    g_battle_real_coord_delta.y = (values->y << 12) / animation_frames;
}
