#include "psx/types.h"

extern void transition_map_ambient_light_color(s32 frame_duration,
    const u8* color);

void battle_set_map_ambient_light_color(s32 frame_duration, const u8* color) {
    transition_map_ambient_light_color(frame_duration, color);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
