#include "fft/data.h"

extern s32 g_world_thread_task_ids[][256];

void world_set_thread_task_id(s32 task_id) {
    g_world_thread_task_ids[g_world_current_thread_id][0] = task_id;
}
