#include "fft/opening.h"

extern void open_set_sound_type_and_volume(s32 type, s32 volume);
extern s32 func_80018058(void);
extern void func_80017f6c(s32 sound_type);
extern void open_initialize_screen_environments(s32 clear_first);
extern void open_initialize_mdec_stream_state(
    void* state, s32 x, s32 y, s32 width, s32 height);
extern void open_initialize_movie_stream(s32 sector, void* output_callback);
extern s32 CdRead2(s32 mode);
extern s32 open_decode_next_movie_frame(void* state);
extern void reset_cd_subsystems(void);
extern u32 g_open_runtime_flags;
extern u8 g_open_movie_output_callback[];
extern u8 g_open_screen_environments[];
extern s32 g_open_movie_aligned_height;
extern u32 g_open_movie_width;
extern u32 g_open_movie_current_frame;
extern s32 g_open_movie_stream_status;
extern u32 g_open_movie_first_frame;
extern s32 g_open_movie_last_frame;
extern s32 g_open_current_openbk_image_id;

void open_stream_movie(
    s32 sector,
    s32 first_frame,
    s32 last_frame,
    s32 sound_type) {
    open_set_sound_type_and_volume(0, 1);
    func_80017f6c(func_80018058());
    g_open_runtime_flags |= 0x3000;
    open_initialize_screen_environments(1);

    g_open_movie_aligned_height = 0;
    g_open_movie_width = 0;
    g_open_movie_current_frame = 0;
    g_open_movie_stream_status = 0;
    g_open_movie_first_frame = first_frame;
    g_open_movie_last_frame = last_frame;
    open_initialize_mdec_stream_state(
        &g_open_mdec_stream_state, 0, 8, 0, 0xf8);

    for (;;) {
        open_initialize_movie_stream(sector, g_open_movie_output_callback);
        while (CdRead2(0x1e0) == 0) {
        }
        if (open_decode_next_movie_frame(&g_open_mdec_stream_state) != 0) {
            break;
        }
        reset_cd_subsystems();
    }

    open_set_sound_type_and_volume(sound_type, 0x20);
    PutDrawEnv(g_open_screen_environments);
    PutDispEnv(g_open_screen_environments + 0x5c);
    g_open_current_openbk_image_id = -1;
    g_open_runtime_flags = (g_open_runtime_flags & ~0x180) | 6;
}
