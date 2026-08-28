#include "fft/opening.h"

extern void* open_acquire_next_movie_frame(open_mdec_stream_state_t* state);
extern void DecDCTvlc(void* frame_data, void* decode_buffer);
extern void StFreeRing(void* frame_data);

s32 open_decode_next_movie_frame(open_mdec_stream_state_t* state) {
    void* frame_data;
    s32 result;

    frame_data = open_acquire_next_movie_frame(state);
    if (frame_data != 0) {
        state->vlc_buffer_index = !state->vlc_buffer_index;
        DecDCTvlc(frame_data, state->vlc_buffers[state->vlc_buffer_index]);
        StFreeRing(frame_data);
        result = 1;
    } else {
        result = 0;
    }

    return result;
}
