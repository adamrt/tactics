#include "psx/types.h"

extern void equip_set_thread_completion_parameters(s32 idx);
extern s32 is_event_thread_running(s32 idx);
extern void initialize_event_thread(s32 idx, void* arg1);
extern void battle_store_thread_function_parameters(s32 idx, void* arg1, s32 arg2, s32 arg3);

extern s32 D_801CE1B4;
extern s32 D_801C31C4;

extern s32 D_801CE414;
extern s32 D_801CE1B0;

void equip_toggle_event_thread_11(s32 enable) {
    if (enable != 0) {
        if (is_event_thread_running(0xB) == 0) {
            initialize_event_thread(0xB, &D_801C31C4);
            battle_store_thread_function_parameters(0xB, &D_801CE1B4, 0, 0);
        }
    } else {
        equip_set_thread_completion_parameters(0xB);
    }
    D_801CE414 = enable;
    D_801CE1B0 = enable;
}
