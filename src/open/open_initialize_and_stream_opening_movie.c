#include "psx/types.h"

extern void main_unload_scenario_music_and_tunes(void);
extern void open_initialize_runtime_state(void);
extern void open_load_main_menu_graphics(void);
extern void open_initialize_screen_environments(s32 clear_first);
extern void open_initialize_render_buffers(void);
extern void open_initialize_directional_input_state(void);
extern void open_stream_opening_movie(s32 skip_movie);

void open_initialize_and_stream_opening_movie(s32 skip_movie) {
    main_unload_scenario_music_and_tunes();
    open_initialize_runtime_state();
    open_load_main_menu_graphics();
    open_initialize_screen_environments(1);
    open_initialize_render_buffers();
    open_initialize_directional_input_state();
    open_stream_opening_movie(skip_movie);
}
