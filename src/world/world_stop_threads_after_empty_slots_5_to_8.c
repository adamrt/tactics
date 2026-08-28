#include "fft/data.h"

extern void world_mark_thread_stopped(s32 thread_id);

void world_stop_threads_after_empty_slots_5_to_8(void) {
    s32 thread_id = 8;

    do {
        world_thread_t* thread = &g_world_threads[thread_id];

        if (thread->is_running == 0) {
            world_mark_thread_stopped(thread_id + 1);
        }
        thread_id--;
    } while (thread_id >= 5);
}
