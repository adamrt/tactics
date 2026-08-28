#include "psx/types.h"

extern void equip_set_thread_completion_parameters(s32);
extern s32 is_event_thread_running(s32);
extern void initialize_event_thread(s32, void*);
extern void func_8014CA38(s32, void*, s32, s32);

extern u8 D_801C31C4[];
extern u8 D_801CE1A0[];

void equip_toggle_event_thread_12(s32 arg0) {
    if (arg0 != 0) {
        if (is_event_thread_running(0xC) == 0) {
            initialize_event_thread(0xC, D_801C31C4);
            func_8014CA38(0xC, D_801CE1A0, 0, 0);
        }
    } else {
        equip_set_thread_completion_parameters(0xC);
    }
}
