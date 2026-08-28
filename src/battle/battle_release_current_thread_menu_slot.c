#include "psx/types.h"

extern s32 g_current_event_thread_id;
extern s32 g_battle_menu_slot_owner_thread_ids[3];
extern s32 g_battle_menu_slot_states[3];

void battle_release_current_thread_menu_slot(void) {
    s32 index;
    s32 current_thread_id;
    s32* owner_thread_id;
    s32* slot_state;

    index = 0;
    current_thread_id = g_current_event_thread_id;
    slot_state = g_battle_menu_slot_states;
    owner_thread_id = g_battle_menu_slot_owner_thread_ids;
    for (;;) {
        if (current_thread_id == *owner_thread_id) {
            *owner_thread_id = 0;
            *slot_state = 0;
            return;
        }
        slot_state++;
        index++;
        owner_thread_id++;
        if (index >= 3) {
            return;
        }
    }
}
