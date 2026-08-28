#include "psx/types.h"

extern s32 D_801d92b8;
extern u8 g_card_last_written_save_slot;
extern s8 g_card_save_slot_file_states[];
extern u8 g_card_state_801c9570;
extern s16 g_card_state_801c9572;
extern s16 g_card_state_801c9576;

extern void card_update_save_slot_scroll(s32 index);

s32 card_initialize_occupied_save_slot_selection(void) {
    s32 slot;
    s32 occupied_count;

    D_801d92b8 = 0;
    slot = 0;
    occupied_count = 0;
    while (slot < 15) {
        if (slot == g_card_last_written_save_slot) {
            g_card_state_801c9576 = slot;
            g_card_state_801c9570 = occupied_count;
        }
        if (g_card_save_slot_file_states[slot] != -1) {
            occupied_count++;
        }
        slot++;
    }

    slot = 0;
    while (slot < 10) {
        card_update_save_slot_scroll(g_card_state_801c9570);
        if (g_card_state_801c9572 == 0) {
            slot++;
        } else {
            slot = 0;
        }
    }
    return occupied_count;
}
