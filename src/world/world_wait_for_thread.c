#include "fft/data.h"

void world_wait_for_thread(s32 thread_id) {
    do {
        world_switch_to_next_thread();
    } while (g_world_threads[thread_id].is_running != 0);
}
