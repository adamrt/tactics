#include "psx/types.h"

enum {
    MAP_TEXTURE_ANIMATION_LAST_OFFSET = 70,
    MAP_TEXTURE_ANIMATION_STATE_BYTES = 10,
};

extern u8 g_map_texture_animation_states[];

void battle_reset_map_texture_animations(void) {
    s32 offset;

    offset = MAP_TEXTURE_ANIMATION_LAST_OFFSET;
    do {
        g_map_texture_animation_states[offset] = 0;
        offset -= MAP_TEXTURE_ANIMATION_STATE_BYTES;
    } while (offset >= 0);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
