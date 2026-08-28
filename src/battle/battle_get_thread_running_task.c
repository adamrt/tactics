#include "psx/types.h"

extern s32 battle_check_thread_running_status(s32 thread_id);
extern s32 g_current_event_thread_id;
extern u8 g_event_thread_task_array[];

/* Return the id of any OTHER live event thread whose current task word
   equals task_id, or 0 when none matches. Skips the caller's own thread
   (g_current_event_thread_id) and slot 0. */
s32 battle_get_thread_running_task(s32 task_id) {
    s32 thread_id;
    s32 task_offset;

    thread_id = 1;
    task_offset = 0x400;
    do {
        if (thread_id != g_current_event_thread_id
            && battle_check_thread_running_status(thread_id) != 0
            && *(s32*)(g_event_thread_task_array + task_offset) == task_id) {
            return thread_id;
        }
        thread_id += 1;
        task_offset += 0x400;
    } while (thread_id < 0x10);
    return 0;
}
