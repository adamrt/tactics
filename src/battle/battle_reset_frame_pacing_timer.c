#include "psx/types.h"

extern s32 g_frame_pacing_timer;

void battle_reset_frame_pacing_timer(void) {
    g_frame_pacing_timer = 0;
}
