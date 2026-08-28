#include "fft/data.h"

void world_stop_current_thread(void) {
    g_world_threads[g_world_current_thread_id].is_running = 0;
    g_world_threads[g_world_current_thread_id].task_id = 0;
    world_switch_to_next_thread();
}
