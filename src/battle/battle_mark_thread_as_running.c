#include "psx/types.h"

extern s32 (*g_event_threads)[256];

void battle_mark_thread_as_running(s32 thread_id) {
    g_event_threads[thread_id][0x12] = 1;
}
