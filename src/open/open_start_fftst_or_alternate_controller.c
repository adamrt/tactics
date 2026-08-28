#include "psx/types.h"

extern s32 g_open_current_controller_index;
extern s32 g_open_display_buffer_index;

extern void open_stream_fftst_and_push_controller(s32 start_sector,
    s32 stream_length,
    s32 end_frame,
    s32 frame_count);
extern void func_8006A174(s32 argument);

void open_start_fftst_or_alternate_controller(s32 use_alternate) {
    g_open_current_controller_index = 0;
    if (use_alternate == 0) {
        g_open_display_buffer_index = 0;
        open_stream_fftst_and_push_controller(0x153D6, 0x278A, 0x3DF, 0x2DE);
    } else {
        func_8006A174(0);
    }
}
