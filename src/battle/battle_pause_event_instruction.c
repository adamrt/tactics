#include "psx/types.h"

extern void switch_to_next_thread(void);
extern s32 battle_get_current_thread_task_id(void);
extern s32 g_battle_event_input;

void battle_pause_event_instruction(void) {
    do {
        switch_to_next_thread();
        if (battle_get_current_thread_task_id() == 3) {
            return;
        }
    } while ((g_battle_event_input & 0x160) == 0);
}
