#include "fft/opening.h"

extern s32 g_open_formation_entry_mask;
extern u8 g_open_text_section_offsets;

void func_800e8698(void);
void world_initialize_text_format_section_pointers(void* offset_table);
void func_800e4d9c(void);
void world_initialize_thread(s32 thread_index, void (*entry)(void));
void world_store_thread_function_parameters(
    s32 thread_index,
    s32 function_index,
    s32 parameter_0,
    s32 parameter_1);
void main_play_sound(s32 sound_id);

/* The thread-2 controller record reuses the first two words as
 * run_followup (0x00) and result (0x04). */
void open_start_thread_2_controller(s32 parameter, s32 run_followup) {
    {
        s32 controller = g_open_current_controller_index;

        g_open_controller_stream_start[controller].stream_start = run_followup;
    }
    if (run_followup != 0) {
        func_800e8698();
        world_initialize_text_format_section_pointers(&g_open_text_section_offsets);
    }

    world_initialize_thread(2, func_800e4d9c);
    world_store_thread_function_parameters(2, 0x33, parameter, 0);

    {
        s32 controller = g_open_current_controller_index;
        s32 previous_mask = g_open_formation_entry_mask;

        g_open_formation_entry_mask = -1;
        g_open_controller_stream_start[controller].stream_length = previous_mask;
    }
    main_play_sound(0x12);

    {
        s32 controller = g_open_current_controller_index;
        s32 next_controller = controller + 1;

        g_open_controller_handler_indices[controller] = 8;
        g_open_current_controller_index = next_controller;
    }
}
