#include "psx/types.h"

extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void* fn);
extern void battle_store_thread_function_parameters(s32 thread_id, void* args, s32 a2, s32 a3);
extern void bunit_out_message_thread_to_stop(s32 thread_id);
extern void func_801BF954(void);
extern u32 D_801CF4B8;

/* BUNIT.OUT 001c3ee0 - Start (arg=1) or stop (arg=0) sub-thread 8, invoking
 * func_801BF954 with parameter block D_801CF4B8. */
void bunit_toggle_event_thread_8(s32 enable) {
    if (enable != 0) {
        if (is_event_thread_running(8) == 0) {
            initialize_event_thread(8, func_801BF954);
            battle_store_thread_function_parameters(8, &D_801CF4B8, 0, 0);
        }
    } else {
        bunit_out_message_thread_to_stop(8);
    }
}
