#include "psx/types.h"

extern s32 g_card_thread_state;
extern s32 is_event_thread_running(s32 id);
extern void func_801c3a4c(s32* output, s32 value0, s32 value1);
extern void card_set_thread_completion_parameters(s32 id);

void card_wait_for_thread_and_clear_state(s32 id) {
    s32 output;

    while (is_event_thread_running(id) != 0) {
        card_set_thread_completion_parameters(id);
        func_801c3a4c(&output, 0, 0);
    }
    g_card_thread_state = 0;
}
