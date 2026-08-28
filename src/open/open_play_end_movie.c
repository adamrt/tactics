#include "psx/types.h"

extern s32 g_active_graphics_buffer_index;
extern s32 g_open_current_controller_index;
extern void open_stream_fftend(s32 start, s32 size, s32 sectors);

void open_play_end_movie(void) {
    g_open_current_controller_index = 0;
    g_active_graphics_buffer_index = 0;
    open_stream_fftend(0x21908, 0x3858, 0x571);
}
