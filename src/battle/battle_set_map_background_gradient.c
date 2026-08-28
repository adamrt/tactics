#include "psx/types.h"

extern void transition_map_background_gradient(s32 frame_duration,
    const u8* colors);

void battle_set_map_background_gradient(s32 frame_duration, const u8* colors) {
    transition_map_background_gradient(frame_duration, colors);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
