#include "psx/types.h"

extern s32 g_world_task_thread_active;

s32 world_is_task_thread_active(void) {
    return g_world_task_thread_active;
}
