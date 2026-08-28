#include "psx/types.h"

extern u32 g_open_overlay_fade_flags;
extern u32 g_open_overlay_fade_frame;
extern u32 g_open_overlay_fade_duration;

void open_start_overlay_fade_out(u32 duration) {
    u32* control = &g_open_overlay_fade_flags;
    u32 flags = *control;

    g_open_overlay_fade_duration = duration;
    g_open_overlay_fade_frame = 0;
    *control = flags | 5;
}
