#include "fft/opening.h"

extern void StRingStatus(s16* free_sectors, s16* read_sectors);
extern s32 StGetBacklog(s32* backlog);
extern void func_800212cc(s32 channel, s32 mask, s32 end_frame);
extern void open_start_cd_stream_read(s32* backlog);
extern void DecDCTin(void* input, s32 mode);
extern void DecDCTout(void* output, s32 words);
extern s32 open_decode_next_movie_frame(open_mdec_stream_state_t* state);
extern void open_wait_for_mdec_output(open_mdec_stream_state_t* state, s32 unused);
extern void open_stop_movie_stream(s32 completed);

extern u32 g_open_runtime_flags;
extern s16 g_open_mdec_slice_width;
extern s16 g_open_mdec_slice_height;
extern s32 g_open_movie_stream_status;

void open_process_movie_stream_frame(void) {
    struct {
        s32 backlog;
        u8 padding_04[4];
        s16 free_sectors;
        s16 read_sectors;
        u8 padding_0c[4]; /* 16-byte block at sp+0x10 */
    } status;
    /* One pin: the multiplicand must sit in $a1 (GCC picks $v1). */
    register s32 slice_width __asm__("$5");
    s32 words;

    if ((g_open_runtime_flags & 2) == 0) {
        return;
    }

    StRingStatus(&status.free_sectors, &status.read_sectors);
    if (status.free_sectors < 16) {
        func_800212cc(1, StGetBacklog(&status.backlog), -1);
        open_start_cd_stream_read(&status.backlog);
    }

    DecDCTin(g_open_mdec_stream_state.vlc_buffers[g_open_mdec_stream_state.vlc_buffer_index], 3);
    slice_width = g_open_mdec_slice_width;
    words = slice_width * g_open_mdec_slice_height;
    DecDCTout(g_open_mdec_stream_state.output_buffers[g_open_mdec_stream_state.output_buffer_index],
        words / 2);
    open_decode_next_movie_frame(&g_open_mdec_stream_state);
    open_wait_for_mdec_output(&g_open_mdec_stream_state, 0);

    if (g_open_movie_stream_status == 1) {
        open_stop_movie_stream(1);
    }
    if (g_open_movie_stream_status == 2) {
        open_stop_movie_stream(0);
    }
}
