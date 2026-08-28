#include "psx/types.h"

extern s32 g_current_event_thread_id;
extern s32 g_battle_thread_task_ids[][256];

s32 battle_get_current_thread_task_id(void) {
    return g_battle_thread_task_ids[g_current_event_thread_id][0];
}
