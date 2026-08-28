#include "psx/types.h"

enum {
    MAP_TEXTURE_ANIMATION_CAPACITY = 8,
    MAP_TEXTURE_ANIMATION_STATE_BYTES = 10,
};

extern u8 g_map_texture_animation_states[];

s32 battle_stop_map_texture_animation(s32 handle) {
    if ((u32)(handle - 1) < MAP_TEXTURE_ANIMATION_CAPACITY) {
        g_map_texture_animation_states
            [handle * MAP_TEXTURE_ANIMATION_STATE_BYTES] = 0;
        return 1;
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
