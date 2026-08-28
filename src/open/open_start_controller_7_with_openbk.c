#include "fft/opening.h"

extern void open_build_openbk_file_header(s32 file_index, void* destination);
extern void open_wait_for_pending_file(void);
extern void world_set_event_speed(s32 value);
extern void open_start_overlay_fade_out(s32 duration);

extern void* g_open_file_destination;
extern s16 D_800855F4[96];
extern s16 D_8008E434[96];
extern s32 g_open_formation_entry_mask;
extern s32 g_open_formation_otag_index;
extern s32 g_open_runtime_flags;

void open_start_controller_7_with_openbk(void) {
    s32 i;
    s32 four;
    s32 controller;

    open_build_openbk_file_header(1, g_open_file_destination);
    open_wait_for_pending_file();

    for (i = 0; i < 96; i++) {
        D_8008E434[i] = i + 0xc000;
        D_800855F4[i] = 0;
    }

    world_set_event_speed(1);
    g_open_formation_entry_mask = 0x160;
    /* The same 4 is stored twice; the local keeps it in a saved register
     * across the fade-out call instead of being rematerialized. */
    four = 4;
    g_open_formation_otag_index = four;
    g_open_runtime_flags |= 0x400;
    open_start_overlay_fade_out(0x20);

    controller = g_open_current_controller_index;
    g_open_controller_stream_start[controller].stream_start = 0;
    g_open_controller_stream_start[controller].stream_length = 0;
    g_open_controller_stream_start[controller].field_08 = 0;
    g_open_controller_stream_start[controller].field_0c = four;
    g_open_controller_stream_start[controller].field_10 = 0;
    g_open_controller_handler_indices[controller] = 7;
    g_open_current_controller_index = controller + 1;
}
