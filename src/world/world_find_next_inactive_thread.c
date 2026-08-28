#include "fft/data.h"

extern s32 world_check_thread_running_status_by_id(s32 thread_id);

s32 world_find_next_inactive_thread(s32 thread_id) {
    s32 index;

    if (thread_id < 16) {
        return thread_id;
    }

    index = g_world_current_thread_id + 1;
    if (index >= 17) {
        world_stop_current_thread();
    } else {
        do {
            if (world_check_thread_running_status_by_id(index) == 0) {
                return index;
            }
            index++;
        } while (index < 17);

        world_stop_current_thread();
    }
}
