#include "psx/types.h"

extern s32 g_world_current_thread_id;
extern s32 g_world_thread_task_ids[][256];

s32 world_get_thread_task_id(void) {
    return g_world_thread_task_ids[g_world_current_thread_id][0];
}
