#include "fft/opening.h"

extern u32 g_open_runtime_flags;

extern void open_stream_movie(
    s32 start_sector,
    s32 end_frame,
    s32 frame_count,
    s32 frame_rate);

void open_stream_fftst_and_push_controller(
    s32 start_sector,
    s32 stream_length,
    s32 end_frame,
    s32 frame_count) {
    s32 controller;

    open_stream_movie(start_sector, end_frame, frame_count, 0x76);
    g_open_runtime_flags &= ~0x40;
    controller = g_open_current_controller_index;
    g_open_controller_stream_start[controller].stream_start = start_sector;
    g_open_controller_stream_start[controller].stream_length = stream_length;
    g_open_controller_handler_indices[controller] = 0;
    g_open_current_controller_index = controller + 1;
}

/* A new controller starts in handler state zero. */
