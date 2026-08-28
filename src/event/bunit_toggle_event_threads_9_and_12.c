#include "psx/types.h"

extern u32 D_801CF4C0;
extern u8 D_801CF4E0;
extern u8 D_801CF4F4;
extern void func_801C0D54(void);
extern void func_801C1BA8(void);
extern s32 battle_check_thread_r4_running_status(s32 id);
extern void battle_thread_initialize(s32 id, void (*func)(void));
extern void battle_store_thread_function_parameters(s32 id, void* a1, s32 a2, s32 a3);
extern void bunit_out_message_thread_to_stop(s32 id);

/* Start (enable=1) or stop (enable=0) sub-threads 9 and 12. Sister of
 * bunit_toggle_event_thread_7 / _8. */
void bunit_toggle_event_threads_9_and_12(s32 enable) {
    if (enable != 0) {
        if (D_801CF4C0 & 0x60) {
            return;
        }
        if (battle_check_thread_r4_running_status(9) != 0) {
            return;
        }
        battle_thread_initialize(9, func_801C0D54);
        battle_store_thread_function_parameters(9, &D_801CF4E0, 0, 0);
        battle_thread_initialize(0xC, func_801C1BA8);
        battle_store_thread_function_parameters(0xC, &D_801CF4F4, 0, 0);
    } else {
        bunit_out_message_thread_to_stop(9);
        bunit_out_message_thread_to_stop(0xC);
    }
}
