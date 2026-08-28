#include "psx/types.h"

enum {
    MAP_TEXTURE_ANIMATION_CAPACITY = 8,
};

typedef struct MapTextureAnimationState {
    u8 active;
    u8 elapsed_frames;
    u8 frame_duration;
    u8 padding_03;
    u16 polygon_group;
    u16 first_polygon;
    u16 last_polygon;
} MapTextureAnimationState;

extern MapTextureAnimationState g_map_texture_animation_states[];

s32 battle_start_map_texture_animation(u8 frame_duration, u16 polygon_group,
    u16 first_polygon, u16 last_polygon) {
    s32 index;
    s32 active;
    s32 result;
    MapTextureAnimationState* state;

    index = 0;
    active = 1;
    state = g_map_texture_animation_states;

loop:
    if (state->active != 0) {
        goto occupied;
    }
    result = index + 1;
    state->active = active;
    state->polygon_group = polygon_group;
    state->first_polygon = first_polygon;
    state->last_polygon = last_polygon;
    state->frame_duration = frame_duration;
    return result;

occupied:
    index++;
    if (index < MAP_TEXTURE_ANIMATION_CAPACITY) {
        state++;
        goto loop;
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
