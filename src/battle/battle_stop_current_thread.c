#include "psx/types.h"

extern s32 (*g_event_threads)[256];
extern s32 g_current_event_thread_id;
extern void switch_to_next_thread(void);

void battle_stop_current_thread(void) {
    g_event_threads[g_current_event_thread_id][0x12] = 0;
    g_event_threads[g_current_event_thread_id][0x13] = 0;
    switch_to_next_thread();
}
