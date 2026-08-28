#include "psx/types.h"

extern s32 g_frame_pacing;

void battle_clear_frame_pacing(void) {
    g_frame_pacing = 0;
}
