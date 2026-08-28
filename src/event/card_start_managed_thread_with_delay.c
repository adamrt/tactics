#include "psx/types.h"

typedef struct CardThreadDescriptor {
    u8 unknown_00[0x28];
    void (*entry)(void);
} CardThreadDescriptor;

extern s32 g_card_thread_state;
extern CardThreadDescriptor* g_card_thread_descriptor;
extern void card_wait_for_thread_and_clear_state(s32 thread_id);
extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2);
extern void func_801c3a4c(void* state, s32 arg1, s32 arg2);

void card_start_managed_thread_with_delay(s32 thread_id,
    CardThreadDescriptor* descriptor) {
    s32 state[2];
    s32 i;

    if (g_card_thread_state == 0) {
        card_wait_for_thread_and_clear_state(thread_id);
        g_card_thread_descriptor = descriptor;
        initialize_event_thread(thread_id, descriptor->entry);
        battle_store_thread_function_parameters(thread_id,
            (s32)g_card_thread_descriptor, 0, 0);
        for (i = 0; i < 20; i++) {
            func_801c3a4c(state, 0, 0);
        }
        g_card_thread_state = 1;
    } else {
        g_card_thread_state = is_event_thread_running(thread_id);
    }
}
