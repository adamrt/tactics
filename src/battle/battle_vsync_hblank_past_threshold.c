#include "psx/types.h"

extern s32 VSync(s32 mode);

s32 battle_vsync_hblank_past_threshold(void) {
    return VSync(1) >= 0x145;
}
