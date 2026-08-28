#include "psx/types.h"

extern s32 (*g_event_threads)[256];

void battle_store_thread_function_parameters(s32 thread_id, s32 a, s32 b, s32 c) {
    s32* t = g_event_threads[thread_id];
    t[0] = a;
    t[1] = b;
    t[2] = c;
}
