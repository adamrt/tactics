#include "psx/types.h"

extern s32 (*g_event_threads)[256];

s32 battle_check_thread_r4_running_status(s32 thread_id) {
    return g_event_threads[thread_id][0x12];
}
