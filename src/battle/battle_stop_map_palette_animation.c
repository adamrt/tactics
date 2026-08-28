#include "psx/types.h"

enum {
    MAP_PALETTE_ANIMATION_COUNT = 16,
    MAP_PALETTE_ANIMATION_STATE_BYTES = 8,
    MAP_MESH_ANIMATION_DATA_BYTES = 0x982,
};

extern u8 g_map_palette_animation_states[];

void battle_stop_map_palette_animation(s32 mesh_index, s32 animation_index,
    s32 stop_all) {
    s32 index;
    s32 offset;

    if (stop_all == 1) {
        index = MAP_PALETTE_ANIMATION_COUNT - 1;
        offset = mesh_index * MAP_MESH_ANIMATION_DATA_BYTES
            + (MAP_PALETTE_ANIMATION_COUNT - 1)
                * MAP_PALETTE_ANIMATION_STATE_BYTES;
        do {
            g_map_palette_animation_states[offset] = 0;
            index--;
            offset -= MAP_PALETTE_ANIMATION_STATE_BYTES;
        } while (index >= 0);
    } else {
        index = animation_index * MAP_PALETTE_ANIMATION_STATE_BYTES
            + mesh_index * MAP_MESH_ANIMATION_DATA_BYTES;
        g_map_palette_animation_states[index] = 0;
    }
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
