#include "fft/data.h"

s32 world_check_thread_running_status(s32 thread_id) {
    return g_world_threads[thread_id].is_running;
}
