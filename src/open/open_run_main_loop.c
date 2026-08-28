#include "psx/types.h"

extern void open_initialize_and_stream_opening_movie(s32 skip_movie);
extern void open_file_to_ram_center(void* header);
extern void open_clear_and_render_current_frame(void);
extern void open_process_movie_stream_frame(void);
extern void open_update_world_formation_menu(void);
extern void open_dispatch_current_controller(void);
extern void open_render_record_pointer_list(u32* otag, void* records, s32 count);
extern void DrawOtag(u32* otag);
extern void DrawSync(s32 mode);
extern void open_update_button_input_and_check_game_reset(void);
extern s32 VSync(s32 mode);
extern void open_present_movie_frame(void);
extern void tick(void);
extern void SetDispMask(s32 enabled);
extern void open_set_sound_type_and_volume(s32 type, s32 volume);

extern u32 g_open_runtime_flags;
extern u32 g_open_otags[2][16];
extern s32 g_active_graphics_buffer_index;
extern u8 g_open_file_header[];
extern u8 g_open_render_record_pointers[];
extern s32 g_open_render_record_pointer_count;
extern s32 g_open_result;

/* Each of the two otag banks holds 16 words per graphics buffer. */
#define OPEN_OTAG_BUFFER_BYTES 64

s32 open_run_main_loop(s32 skip_movie) {
    u32* otag_0;
    u32* otag_1;

    open_initialize_and_stream_opening_movie(skip_movie);
    if ((g_open_runtime_flags & 1) != 0) {
        otag_0 = g_open_otags[0];
        otag_1 = g_open_otags[1];
        do {
            s32 graphics_buffer_index;
            u32* current_otag;

            open_file_to_ram_center(g_open_file_header);
            open_clear_and_render_current_frame();
            open_process_movie_stream_frame();
            open_update_world_formation_menu();
            open_dispatch_current_controller();

            graphics_buffer_index = g_active_graphics_buffer_index;
            /* index * 64 + bank: the retail addu sums the offset first. */
            current_otag = (u32*)(graphics_buffer_index * OPEN_OTAG_BUFFER_BYTES + (u32)otag_0);
            open_render_record_pointer_list(current_otag, g_open_render_record_pointers,
                g_open_render_record_pointer_count);

            graphics_buffer_index = g_active_graphics_buffer_index;
            current_otag = (u32*)(graphics_buffer_index * OPEN_OTAG_BUFFER_BYTES + (u32)otag_1);
            DrawOtag(current_otag - 1);
            DrawSync(0);
            open_update_button_input_and_check_game_reset();
            VSync(0);
            open_present_movie_frame();
            tick();
        } while ((g_open_runtime_flags & 1) != 0);
    }

    SetDispMask(0);
    open_set_sound_type_and_volume(0xc0, 0x78);
    return g_open_result;
}
