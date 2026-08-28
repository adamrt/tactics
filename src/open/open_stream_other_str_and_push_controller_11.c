#include "fft/opening.h"

extern u32 g_open_runtime_flags;

void open_stream_movie(s32 start_sector, s32 end_frame, s32 frame_count,
    s32 frame_rate);

void open_stream_other_str_and_push_controller_11(
    s32 start_sector, s32 stream_length, s32 end_frame, s32 frame_rate) {
    s32 controller;

    open_stream_movie(start_sector, end_frame, -1, frame_rate);
    g_open_runtime_flags &= ~0x40;
    controller = g_open_current_controller_index;
    g_open_controller_stream_start[controller].stream_start = start_sector;
    g_open_controller_stream_start[controller].stream_length = stream_length;
    g_open_controller_handler_indices[controller] = 11;
    g_open_current_controller_index = controller + 1;
}
