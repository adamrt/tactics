#include "psx/types.h"

extern void equip_set_thread_completion_parameters(s32);
extern s32 is_event_thread_running(s32);
extern void initialize_event_thread(s32, void*);
extern void func_8014CA38(s32, void*, s32, s32);

extern u8 D_801C0318[];
extern u8 D_801CE178[];

void equip_toggle_event_thread_13(s32 arg0) {
    if (arg0 != 0) {
        if (is_event_thread_running(0xD) == 0) {
            initialize_event_thread(0xD, D_801C0318);
            func_8014CA38(0xD, D_801CE178, 0, 0);
        }
    } else {
        equip_set_thread_completion_parameters(0xD);
    }
}
