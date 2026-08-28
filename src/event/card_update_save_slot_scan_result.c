#include "psx/types.h"

enum {
    CARD_LAST_WRITTEN_SAVE_SLOT_NONE = 0xff,
};

extern u8 g_card_last_written_save_slot;
extern s8 g_card_save_slot_file_states[];
extern u8 g_card_queued_sound_effect_id;
extern u8 g_card_state_801c9570;
extern s16 g_card_state_801c9572;
extern s16 g_card_state_801c9574;
extern s16 g_card_state_801c9576;
extern s16 g_card_state_801c9578;
extern u8 g_card_no_save_data_prompt_descriptor[];
extern void* g_card_save_slot_scan_prompt_descriptor;
extern u32 g_card_input_primary_repeat;
extern u8 g_card_save_menu_state;
extern u8 g_card_occupied_save_slot_count;

extern s32 card_poll_operation_result(void);
extern void card_wait_for_thread_and_clear_state(s32 thread_id);
extern void card_start_managed_thread_with_delay(s32 thread_id,
    void* descriptor);
extern s32 card_initialize_occupied_save_slot_selection(void);

void card_update_save_slot_scan_result(void) {
    s32 index;
    s32 all_empty;

    if (card_poll_operation_result() > 0) {
        g_card_save_slot_scan_prompt_descriptor = 0;
        g_card_last_written_save_slot = CARD_LAST_WRITTEN_SAVE_SLOT_NONE;
        card_wait_for_thread_and_clear_state(14);
        card_wait_for_thread_and_clear_state(6);
        g_card_save_menu_state = 3;
    } else if (g_card_save_slot_scan_prompt_descriptor != 0) {
        card_start_managed_thread_with_delay(6, g_card_save_slot_scan_prompt_descriptor);
        if ((g_card_input_primary_repeat & 0x40) != 0 || (g_card_input_primary_repeat & 0x20) != 0) {
            g_card_save_slot_scan_prompt_descriptor = 0;
            g_card_last_written_save_slot = CARD_LAST_WRITTEN_SAVE_SLOT_NONE;
            card_wait_for_thread_and_clear_state(6);
            g_card_save_menu_state = 1;
        }
    } else {
        index = 0;
        all_empty = 1;
        while (index < 15) {
            if (g_card_save_slot_file_states[index] != -1) {
                all_empty = 0;
            }
            index++;
        }

        if (all_empty != 0) {
            g_card_save_slot_scan_prompt_descriptor = g_card_no_save_data_prompt_descriptor;
        }
        if (g_card_save_slot_scan_prompt_descriptor == 0) {
            g_card_state_801c9574 = 24;
            g_card_state_801c9572 = 0;
            g_card_state_801c9578 = 0;
            g_card_state_801c9576 = 0;
            g_card_state_801c9570 = 0;
            g_card_occupied_save_slot_count = card_initialize_occupied_save_slot_selection();
            g_card_save_menu_state = 4;
        } else {
            g_card_queued_sound_effect_id = 0x30;
        }
    }
}
