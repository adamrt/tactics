#include "fft/opening.h"

extern s32* g_open_file_destination;
extern s32 g_open_work_buffer_0[];
extern u8 g_open_render_record_pointers[];
extern s32 g_open_render_record_pointer_count;

s32 open_check_memory_card_slots(void);
void open_begin_new_game_transition(void);
void open_start_overlay_fade_out(s32 duration);
s32 open_append_render_record_36(void* group, void* records);

void open_begin_new_game_or_clear_file_buffer(void) {
    s32* source;
    s32* destination;
    s32 index;
    s32 record;
    s32* position;
    s32 controller;
    s32 card_status;
    s32 frame_padding[2];

    card_status = open_check_memory_card_slots();
    index = 0;
    if (card_status != 0) {
        open_begin_new_game_transition();
        return;
    }

    source = g_open_file_destination;
    destination = g_open_work_buffer_0;
    do {
        *destination = *source;
        index++;
        *source = 0;
        source++;
        destination++;
    } while (index < 0x7800);

    open_start_overlay_fade_out(0x10);
    record = open_append_render_record_36(
        g_open_render_record_pointers, &g_open_render_record_pointer_count);
    g_open_render_records_36[record].field_04 = 0x12;
    g_open_render_records_36[record].field_10 = 0;
    g_open_render_records_36[record].field_0c = 0;
    position = &g_open_render_records_36[record].field_18;
    controller = g_open_current_controller_index;
    position[0] = -4;
    position[1] = -16;
    g_open_controller_stream_start[controller].stream_start = 0;
    g_open_controller_handler_indices[controller] = 12;
    g_open_current_controller_index = controller + 1;
}
