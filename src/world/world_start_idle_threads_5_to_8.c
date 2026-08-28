#include "fft/data.h"

extern void world_initialize_thread(s32 thread_id, void (*function)(void));
extern void world_idle_thread_yield_forever(void);

void world_start_idle_threads_5_to_8(void) {
    s32 thread_id = 8;

    do {
        world_thread_t* thread = &g_world_threads[thread_id];

        if (thread->is_running == 0) {
            world_initialize_thread(thread_id, world_idle_thread_yield_forever);
        }
        thread_id--;
    } while (thread_id >= 5);
}
