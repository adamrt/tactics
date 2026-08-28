#include "psx/types.h"

enum {
    CARD_LAST_WRITTEN_SAVE_SLOT_NONE = 0xff,
};

typedef struct CardSaveBuffer {
    u8 unknown_000[0x100];
    u8 slot;
    u8 unknown_101[0x7f];
} CardSaveBuffer;

extern u8 g_card_last_written_save_slot;
extern s8 g_card_save_slot_file_states[];
extern u8 g_card_save_slot_metadata[][0x18];
extern s32 g_suppress_sound_effect_playback;
extern u8 g_card_queued_sound_effect_id;
extern const char* g_card_save_file_names[];
extern u8 g_card_save_completed;
extern u8 g_card_save_write_phase;
extern u8 g_card_save_in_progress_thread_descriptor[];
extern u8 g_card_save_failure_thread_descriptor[];
extern u8 g_card_save_write_failed;
extern u8 D_801ca964;
extern CardSaveBuffer* g_card_save_buffer_pointer;
extern u8 g_card_save_menu_state;
extern u8 g_card_save_slot_descriptions[][0x50];
extern u32 g_card_input_primary_repeat;

extern void card_populate_save_buffer(s32 slot);
extern void card_start_managed_thread_with_delay(s32 thread_id,
    void* descriptor);
extern void card_wait_for_thread_and_clear_state(s32 thread_id);
extern s32 card_write_buffer_to_file(const char* filename, const void* source,
    s32 size, s32 create_file);
extern s32 card_open_selected_file_with_retries(const char* filename, s32 mode);
extern s32 card_seek_file_with_retries(s32 descriptor, s32 offset, s32 origin);
extern s32 card_write_file_with_retries(s32 descriptor, const void* source,
    s32 size);
extern s32 card_close_file_with_retries(s32 descriptor);
extern void card_build_save_slot_description(s32 first, void* destination);
extern void card_render_save_slot_text(s32 slot);
extern void bcopy(const void* source, void* destination, s32 size);
extern void card_update_save_slot_playtime(s32 slot);

void card_update_save_slot_write_operation(s32 slot) {
    s32 write_result;
    s32 header_result;
    s32 unused_18;
    s32 descriptor;
    s32 unused_20;
    s32 unused_24;
    s32 unused_28;
    s32 unused_2c;
    s32 unused_30;
    s32 unused_34;
    s32 unused_38;
    s32 unused_3c;

    if (g_card_save_write_phase == 0) {
        g_card_save_write_phase = 1;
        g_card_save_write_failed = 0;
        D_801ca964 = 0;
        card_populate_save_buffer(slot);
        card_start_managed_thread_with_delay(
            6, g_card_save_in_progress_thread_descriptor);
        g_suppress_sound_effect_playback = 1;
        return;
    } else {
        if (g_card_save_write_phase < 2) {
            g_card_save_write_phase++;
            return;
        }
    }

    g_suppress_sound_effect_playback = 0;
    if (g_card_save_write_failed != 0) {
        card_start_managed_thread_with_delay(
            6, g_card_save_failure_thread_descriptor);
        if ((g_card_input_primary_repeat & 0x20) != 0 || (g_card_input_primary_repeat & 0x40) != 0) {
            card_wait_for_thread_and_clear_state(6);
            g_card_save_write_phase = 0;
            g_card_save_menu_state = 3;
        }
        return;
    }

    write_result = card_write_buffer_to_file(
        g_card_save_file_names[slot], g_card_save_buffer_pointer, 0x1e00,
        g_card_save_slot_file_states[slot]);
    card_wait_for_thread_and_clear_state(6);
    header_result = 0;
    if (write_result == 0x1e00) {
        g_card_save_buffer_pointer->slot = slot;
        descriptor = card_open_selected_file_with_retries(g_card_save_file_names[slot], 2);
        if (descriptor >= 0) {
            header_result = card_seek_file_with_retries(descriptor, 0x100, 0);
            if (header_result != -1) {
                header_result = card_write_file_with_retries(
                    descriptor, &g_card_save_buffer_pointer->slot, 0x80);
            }
            if (card_close_file_with_retries(descriptor) == 0) {
                header_result = 0;
            }
        }
    }

    if (write_result == 0x1e00 && header_result == 0x80) {
        g_card_save_menu_state = 4;
        g_card_save_slot_file_states[slot] = 0;
        card_build_save_slot_description(0, g_card_save_slot_descriptions[slot]);
        card_render_save_slot_text(slot);
        bcopy(&g_card_save_buffer_pointer->slot, g_card_save_slot_metadata[slot], 0x18);
        card_update_save_slot_playtime(slot);
        g_card_queued_sound_effect_id = 0x85;
        g_card_save_write_phase = 0;
        g_card_save_completed = 1;
        g_card_last_written_save_slot = slot;
        return;
    }

    g_card_last_written_save_slot = CARD_LAST_WRITTEN_SAVE_SLOT_NONE;
    g_card_save_write_failed = 1;
    g_card_queued_sound_effect_id = 0x30;
}
