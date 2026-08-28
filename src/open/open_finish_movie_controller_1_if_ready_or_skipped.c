#include "psx/gpu.h"
#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern u32 g_open_new_button_presses;
extern s32 g_open_current_controller_index;
extern s32 g_open_result;

extern void open_stop_movie_stream(s32 flush_decoder);

void open_finish_movie_controller_1_if_ready_or_skipped(void) {
    u32 flags;
    s32 controller;

    if (!(g_open_runtime_flags & 2)) {
        SetDispMask(0);
        flags = g_open_runtime_flags;
        controller = g_open_current_controller_index;
        g_open_result = 0;
        flags |= 0x40;
        controller--;
        g_open_runtime_flags = flags;
        flags ^= 1;
        g_open_current_controller_index = controller;
        g_open_runtime_flags = flags;
        return;
    }

    if (g_open_new_button_presses & 0x800) {
        open_stop_movie_stream(1);
    }
}

/* State one stops an active stream on Start and performs its pop on the */
/* following update, after movie flag 2 has cleared.                     */
