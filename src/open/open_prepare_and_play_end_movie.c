#include "psx/gpu.h"
#include "psx/types.h"

extern s32 g_open_vsync_mode;

extern void main_unload_scenario_music_and_tunes(void);
extern void open_initialize_runtime_state(void);
extern void open_load_end_movie_graphics(void);
extern void open_initialize_screen_environments(s32 clear_first);
extern void open_initialize_render_buffers(void);
extern void open_play_end_movie(void);

void open_prepare_and_play_end_movie(void) {
    RECT source;

    main_unload_scenario_music_and_tunes();
    open_initialize_runtime_state();

    source.x = 0x3c0;
    source.y = 0x100;
    source.w = 0x40;
    source.h = 0x100;
    MoveImage(&source, 0x3c0, 0);
    DrawSync(0);

    g_open_vsync_mode = 0;
    open_load_end_movie_graphics();
    open_initialize_screen_environments(1);
    open_initialize_render_buffers();
    open_play_end_movie();
}
