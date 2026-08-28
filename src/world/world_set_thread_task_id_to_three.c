#include "fft/data.h"

void world_set_thread_task_id_to_three(s32 thread_id) {
    world_thread_t* thread = &g_world_threads[thread_id];

    thread->task_id = 3;
}
