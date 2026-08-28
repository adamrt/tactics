#include "psx/gpu.h"
#include "psx/types.h"

typedef struct OpenStreamControllerState {
    s32 start_sector;
    s32 stream_length;
} OpenStreamControllerState;

extern u32 g_open_runtime_flags;
extern u32 g_open_new_button_presses;
extern s32 g_open_current_controller_index;

extern void open_stop_movie_stream(s32 flush_decoder);
extern void func_8006A174(s32 next_sector);

void open_finish_stream_controller_if_ready_or_skipped(
    const OpenStreamControllerState* state) {
    if (g_open_runtime_flags & 2) {
        if (!(g_open_new_button_presses & 0x800)) {
            return;
        }

        open_stop_movie_stream(0);
        SetDispMask(0);
        g_open_runtime_flags |= 0x40;
    }

    g_open_current_controller_index--;
    func_8006A174(state->start_sector + state->stream_length);
}

/* An active movie waits for Start; a completed movie advances directly. */
/* The two state words locate the disc sector immediately after the stream. */
