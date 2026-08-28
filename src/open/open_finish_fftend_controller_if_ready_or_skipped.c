#include "psx/gpu.h"
#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern u32 g_open_new_button_presses;
extern s32 g_open_current_controller_index;

extern void open_stop_movie_stream(s32 flush_decoder);
extern void open_push_controller_10(void);

void open_finish_fftend_controller_if_ready_or_skipped(void) {
    u32 flags;
    s32 controller;

    if (!(g_open_runtime_flags & 2)) {
        SetDispMask(0);
        flags = g_open_runtime_flags;
        controller = g_open_current_controller_index;
        flags |= 0x40;
        controller--;
        g_open_runtime_flags = flags;
        g_open_current_controller_index = controller;
        open_push_controller_10();
        return;
    }

    if (g_open_new_button_presses & 0x800) {
        open_stop_movie_stream(1);
    }
}
