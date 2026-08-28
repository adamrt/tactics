#include "fft/battle.h"

extern s32 g_animation_speed;
extern battle_real_coords_t g_battle_real_coord_delta;
extern u16 g_battle_real_coord_countdown;

void battle_set_real_coord_delta_from_values(const battle_real_coords_t* values, s32 frame_count) {
    s32 animation_frames;

    animation_frames = (frame_count & 0xffff) / g_animation_speed;
    g_battle_real_coord_countdown = animation_frames;
    animation_frames = g_battle_real_coord_countdown;
    g_battle_real_coord_delta.x = values->x / animation_frames;
    g_battle_real_coord_delta.z = values->z / animation_frames;
    g_battle_real_coord_delta.y = values->y / animation_frames;
}
