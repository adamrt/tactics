#include "fft/battle.h"

extern s32 g_animation_speed;
extern battle_real_coords_t g_battle_offset_screen_coords;
extern battle_real_coords_t g_battle_offset_screen_coords_fixed;
extern battle_real_coords_t g_battle_real_coord_delta;
extern u16 g_battle_offset_screen_coord_countdown;

void battle_set_offset_screen_coord_delta_from_value(
    const s32* destination_value,
    s32 frame_count) {
    s32 animation_frames;
    s32 current_x;
    s32 current_z;
    s32 current_y;
    s32 delta_x;

    animation_frames = (frame_count & 0xffff) / g_animation_speed;
    current_x = g_battle_offset_screen_coords.x;
    current_z = g_battle_offset_screen_coords.z;
    current_y = g_battle_offset_screen_coords.y;
    g_battle_offset_screen_coords_fixed.x = current_x << 12;
    g_battle_offset_screen_coords_fixed.z = current_z << 12;
    g_battle_offset_screen_coords_fixed.y = current_y << 12;
    delta_x = *destination_value - current_x;
    g_battle_offset_screen_coord_countdown = animation_frames;
    animation_frames = g_battle_offset_screen_coord_countdown;
    g_battle_real_coord_delta.x = (delta_x << 12) / animation_frames;
    g_battle_real_coord_delta.z = ((*destination_value - current_z) << 12) / animation_frames;
    g_battle_real_coord_delta.y = ((*destination_value - current_y) << 12) / animation_frames;
}
