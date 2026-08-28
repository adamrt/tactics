#include "fft/data.h"

s32 world_find_running_thread_at_or_after_4(void) {
    s32 thread_id;
    world_thread_t* thread;

    thread_id = 4;
    thread = &g_world_threads[4];
    do {
        if (thread->is_running == 1) {
            return thread_id;
        }
        thread_id++;
        thread++;
    } while (thread_id < 9);
    return thread_id;
}
