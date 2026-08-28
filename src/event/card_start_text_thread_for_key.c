#include "psx/types.h"

extern s32 g_card_active_thread_key;
typedef struct CardEventThread {
    u8 unknown_00[0x5c];
    s32 field_5c;
    u8 unknown_60[0x3a0];
} CardEventThread;

extern CardEventThread* g_event_threads;
extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2);
extern void text_character_handling_thread(void);

s32 card_start_text_thread_for_key(s32 thread_id, s32 parameter_0, s32 key,
    s32 parameter_2, s32 thread_field_5c) {
    s32 status = is_event_thread_running(thread_id);

    if (status == 0) {
        if (g_card_active_thread_key == key) {
            g_card_active_thread_key = 0;
            return 0;
        }
    }
    if (g_card_active_thread_key == 0) {
        initialize_event_thread(thread_id, text_character_handling_thread);
        battle_store_thread_function_parameters(thread_id, parameter_0, key,
            parameter_2);
        g_card_active_thread_key = key;
        g_event_threads[thread_id].field_5c = thread_field_5c;
        return 1;
    }
    return status;
}
