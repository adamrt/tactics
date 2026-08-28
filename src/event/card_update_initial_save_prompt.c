#include "psx/types.h"

extern u8 g_card_state_801c9570;
extern s16 g_card_state_801c957c;
extern s16 g_card_save_slot_index;
extern u8 g_card_initial_save_prompt_descriptor[];
extern s16 g_card_initial_save_prompt_cursor_index;
extern u8 g_card_initial_prompt_thread_state;
extern u8 g_card_save_menu_state;

extern s32 card_start_managed_thread(s32 thread_id, void* descriptor);

void card_update_initial_save_prompt(void) {
    if (g_card_initial_prompt_thread_state == 0) {
        if (g_card_state_801c957c < 40) {
            g_card_state_801c957c++;
        } else {
            g_card_initial_prompt_thread_state = 1;
            g_card_state_801c9570 = 0;
            g_card_initial_save_prompt_cursor_index = 0;
            g_card_save_slot_index = -1;
        }
    } else {
        g_card_initial_prompt_thread_state = card_start_managed_thread(6, g_card_initial_save_prompt_descriptor);
        if (g_card_initial_prompt_thread_state == 0) {
            if (g_card_save_slot_index != 0) {
                g_card_save_menu_state = 10;
            } else {
                g_card_save_menu_state = 1;
            }
        }
    }
}
