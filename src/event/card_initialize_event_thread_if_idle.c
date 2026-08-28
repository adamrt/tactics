#include "psx/types.h"

extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2);
extern void text_character_handling_thread(void);

void card_initialize_event_thread_if_idle(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2) {
    if (!is_event_thread_running(thread_id)) {
        initialize_event_thread(thread_id, text_character_handling_thread);
        battle_store_thread_function_parameters(thread_id, parameter_0, parameter_1,
            parameter_2);
    }
}
