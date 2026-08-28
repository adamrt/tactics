#include "psx/types.h"

extern u8* g_event_threads;

s32 helpmenu_find_running_thread_at_or_after_4(void) {
    s32 thread_id;
    u8* thread;

    thread_id = 4;
    thread = g_event_threads + 0x1000;
    do {
        if (*(s32*)(thread + 0x48) == 1) {
            return thread_id;
        }
        thread_id++;
        thread += 0x400;
    } while (thread_id < 9);
    return thread_id;
}
