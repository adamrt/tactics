#include "psx/types.h"

extern void advance_event_thread(void);
extern s32 battle_get_thread_running_task(s32 thread_id);
extern s32 battle_get_script_variable(s32 var_id);
extern void battle_load_event(s32 event_id);
extern s32 g_current_battle_event_id;

/* Pump event-thread execution until no thread in slots 4..14 is still
   busy, then commit script variable 0x27 as the newly loaded event id.
   Returns 1 when the event actually changed, 0 when it was already
   current. */
s32 battle_load_next_event(void) {
    s32 task_slot;
    s32 event_id;

    do {
        advance_event_thread();
        for (task_slot = 4; task_slot < 0xF; task_slot++) {
            if (battle_get_thread_running_task(task_slot) != 0) {
                break;
            }
        }
    } while (task_slot != 0xF);

    event_id = battle_get_script_variable(0x27);
    if (event_id == g_current_battle_event_id) {
        return 0;
    }
    battle_load_event(event_id);
    g_current_battle_event_id = event_id;
    return 1;
}
