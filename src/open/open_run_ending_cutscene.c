#include "psx/types.h"

extern void open_prepare_and_play_end_movie(void);
extern void open_file_to_ram_center(void* header);
extern void open_clear_and_render_current_frame(void);
extern void open_process_movie_stream_frame(void);
extern void func_8006e8b0(u32* otag, s32 graphics_buffer_index);
extern void open_dispatch_current_controller(void);
extern void DrawSync(s32 mode);
extern void open_update_button_input_and_check_game_reset(void);
extern s32 VSync(s32 mode);
extern void open_present_movie_frame(void);
extern void DrawOtag(u32* otag);
extern void tick(void);
extern void open_backup_frame_vram_page(void);
extern void SetDispMask(s32 enabled);
extern void open_set_sound_type_and_volume(s32 type, s32 volume);

extern u32 g_open_runtime_flags;
extern u32 g_open_otags[2][16];
extern s32 g_active_graphics_buffer_index;
extern s32 g_open_vsync_mode;
extern u8 g_open_file_header[];

/* Each of the two otag banks holds 16 words per graphics buffer. */
#define OPEN_OTAG_BUFFER_BYTES 64

void open_run_ending_cutscene(void) {
    u32* otag_0;
    u32* otag_1;

    open_prepare_and_play_end_movie();
    if ((g_open_runtime_flags & 1) != 0) {
        otag_0 = g_open_otags[0];
        otag_1 = g_open_otags[1];
        do {
            s32 graphics_buffer_index;
            u32* current_otag;

            open_file_to_ram_center(g_open_file_header);
            open_clear_and_render_current_frame();
            open_process_movie_stream_frame();
            graphics_buffer_index = g_active_graphics_buffer_index;
            /* index * 64 + bank: the retail addu sums the offset first. */
            current_otag = (u32*)(graphics_buffer_index * OPEN_OTAG_BUFFER_BYTES + (u32)otag_0);
            func_8006e8b0(current_otag, graphics_buffer_index);
            open_dispatch_current_controller();
            DrawSync(0);
            open_update_button_input_and_check_game_reset();
            VSync(g_open_vsync_mode);
            open_present_movie_frame();
            current_otag = (u32*)((g_active_graphics_buffer_index ^ 1) * OPEN_OTAG_BUFFER_BYTES + (u32)otag_1);
            DrawOtag(current_otag - 1);
            tick();
        } while ((g_open_runtime_flags & 1) != 0);
    }

    open_backup_frame_vram_page();
    SetDispMask(0);
    open_set_sound_type_and_volume(0xc0, 0x78);
}
