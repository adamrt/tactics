#include "fft/data.h"

void world_mark_thread_running(s32 thread_id) {
    g_world_threads[thread_id].is_running = 1;
}
