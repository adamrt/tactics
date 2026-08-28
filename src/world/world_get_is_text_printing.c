#include "fft/data.h"

s32 world_get_is_text_printing(s32 thread_id) {
    world_thread_t* thread = &g_world_threads[thread_id];

    return thread->task_id == 1;
}
