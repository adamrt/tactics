#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern s32 g_open_current_controller_index;
extern s32 g_open_controller_handler_indices[];

extern void open_stream_movie(
    s32 start_sector,
    s32 end_frame,
    s32 frame_count,
    s32 frame_rate);

void open_stream_movie_and_push_controller_1(
    s32 start_sector,
    s32 unused,
    s32 end_frame) {
    s32 controller;

    (void)unused;
    open_stream_movie(start_sector, end_frame, -1, 0x94);
    g_open_runtime_flags &= ~0x40;
    controller = g_open_current_controller_index;
    g_open_controller_handler_indices[controller] = 1;
    g_open_current_controller_index = controller + 1;
}

/* This variant starts handler state one and uses movie rate 0x94. */
