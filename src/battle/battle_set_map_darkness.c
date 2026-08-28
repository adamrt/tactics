#include "psx/types.h"

extern void transition_map_darkness(s32 mode, s32 frame_duration, s16 red,
    s16 green, s16 blue);

void battle_set_map_darkness(s32 mode, s32 frame_duration, s16 red, s16 green,
    s16 blue) {
    transition_map_darkness(mode, frame_duration, red, green, blue);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
