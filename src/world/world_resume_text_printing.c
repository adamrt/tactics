#include "fft/data.h"

void world_resume_text_printing(s32 thread_id) {
    world_thread_t* thread = &g_world_threads[thread_id];

    if (thread->task_id == 0x33) {
        thread->task_id = 1;
        thread->function_parameter_2 = 0xffff;
    }
}
