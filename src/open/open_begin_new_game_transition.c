#include "fft/opening.h"

extern void suzuki_change_volume_balance(s32 value, s32 channel);
extern void main_set_current_music_track(s32 track);
extern void open_load_sound_menu_textures(void);
extern void open_build_openbk_file_header(s32 image_id, void* destination);
extern void open_wait_for_pending_file(void);
extern void open_initialize_transition_request(s32 target, s32 mode, s32 data);
extern void open_start_overlay_fade_out(u32 duration);

extern void* g_open_file_destination;
extern s32 D_80070CB4;

void open_begin_new_game_transition(void) {
    s32 controller;
    s32 stack_padding[4];

    suzuki_change_volume_balance(0, 1);
    main_set_current_music_track(0x22);
    suzuki_change_volume_balance(0x3fff, 5);
    open_load_sound_menu_textures();
    open_build_openbk_file_header(1, g_open_file_destination);
    open_wait_for_pending_file();
    open_initialize_transition_request(12, 3, D_80070CB4);
    open_start_overlay_fade_out(0x20);

    controller = g_open_current_controller_index;
    g_open_controller_stream_start[controller].field_10 = 0;
    g_open_controller_handler_indices[controller] = 4;
    g_open_current_controller_index = controller + 1;
}

/* The title-menu callers enter this path for the new-game selection. */
