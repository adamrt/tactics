#include "psx/types.h"

enum {
    CARD_LAST_WRITTEN_SAVE_SLOT_NONE = 0xff,
};

extern u8 g_card_last_written_save_slot;
extern u8 g_card_selected_save_slot;
extern s32 g_text_substitution_value_0;
extern u8 g_card_state_801c9570;
extern s16 g_card_save_slot_index;
extern s8 g_card_save_completed;
extern u8 g_card_memory_card_slot_selection_descriptor[];
extern s16 g_card_memory_card_slot_cursor_index;
extern u8 g_card_slot_selection_thread_state;
extern u8 g_card_save_menu_state;

extern s32 card_start_managed_thread(s32 thread_id, void* descriptor);
extern void card_set_selected_slot(s32 slot);

void card_update_memory_card_slot_selection(void) {
    if (g_card_slot_selection_thread_state == 0) {
        g_card_slot_selection_thread_state = 1;
        g_card_state_801c9570 = 0;
        g_card_memory_card_slot_cursor_index = g_card_selected_save_slot;
        g_card_save_slot_index = -1;
    }

    g_card_slot_selection_thread_state = card_start_managed_thread(6, g_card_memory_card_slot_selection_descriptor);
    if (g_card_slot_selection_thread_state == 0) {
        if (g_card_save_slot_index == -1) {
            if (g_card_save_completed != 0) {
                g_card_save_menu_state = 10;
            } else {
                g_card_save_menu_state = 0;
            }
        } else {
            g_text_substitution_value_0 = g_card_save_slot_index + 1;
            if (g_card_selected_save_slot != g_card_save_slot_index) {
                g_card_last_written_save_slot = CARD_LAST_WRITTEN_SAVE_SLOT_NONE;
            }
            g_card_selected_save_slot = g_card_save_slot_index;
            card_set_selected_slot(g_card_save_slot_index);
            g_card_save_menu_state = 3;
        }
    }
}
