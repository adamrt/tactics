#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern s32 g_active_graphics_buffer_index;
extern s32 g_open_current_controller_index;
extern u32 g_open_new_button_presses;

void SetDispMask(s32 enabled);
void open_stream_fftst_and_push_controller(s32 start_sector, s32 stream_length,
    s32 end_frame, s32 frame_count);
void open_stop_movie_stream(s32 skipped);

void open_start_fftst_or_skip_movie_controller(void) {
    if ((g_open_runtime_flags & 2) == 0) {
        SetDispMask(0);
        g_active_graphics_buffer_index = 1;
        g_open_runtime_flags |= 0x40;
        g_open_current_controller_index--;
        open_stream_fftst_and_push_controller(0x153d6, 0x278a, 0x3df,
            0x2de);
    } else if ((g_open_new_button_presses & 0x800) != 0) {
        open_stop_movie_stream(1);
    }
}
