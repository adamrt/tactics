#include "psx/types.h"

extern void equip_set_thread_completion_parameters(s32);
extern void initialize_event_thread(s32, void*);
extern s32 is_event_thread_running(s32);
extern void battle_store_thread_function_parameters(s32, void*, s32, s32);
extern void equip_toggle_event_thread_12(s32);
extern u8 D_801C1744[];
extern u8 D_801CE18C[];

void equip_toggle_event_threads_10_and_12(s32 enable) {
    if (enable != 0) {
        if (is_event_thread_running(0xA) == 0) {
            initialize_event_thread(0xA, D_801C1744);
            battle_store_thread_function_parameters(0xA, D_801CE18C, 0, 0);
        }
        equip_toggle_event_thread_12(enable);
        return;
    }
    equip_set_thread_completion_parameters(0xA);
    equip_set_thread_completion_parameters(0xC);
}
