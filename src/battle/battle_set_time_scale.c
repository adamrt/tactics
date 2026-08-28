#include "psx/types.h"

extern s32 g_frame_pacing;

void battle_set_time_scale(s32 value) {
    if ((u32)(value - 1) < 9) {
        g_frame_pacing = value;
    }
}
