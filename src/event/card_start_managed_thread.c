#include "psx/types.h"

typedef struct CardThreadDescriptor {
    u8 unknown_00[0x28];
    void (*entry)(void);
} CardThreadDescriptor;

extern s32 g_card_thread_state;
extern CardThreadDescriptor* g_card_thread_descriptor;
extern s32 is_event_thread_running(s32 thread_id);
extern void initialize_event_thread(s32 thread_id, void (*entry)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 parameter_0,
    s32 parameter_1, s32 parameter_2);

s32 card_start_managed_thread(s32 thread_id, CardThreadDescriptor* descriptor) {
    if (g_card_thread_state == 0) {
        if (is_event_thread_running(thread_id) != 0) {
            return 1;
        }
        g_card_thread_descriptor = descriptor;
        initialize_event_thread(thread_id, descriptor->entry);
        battle_store_thread_function_parameters(thread_id,
            (s32)g_card_thread_descriptor, 0, 0);
        g_card_thread_state = 1;
        return 1;
    }
    g_card_thread_state = is_event_thread_running(thread_id);
    return g_card_thread_state;
}
