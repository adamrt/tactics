#include "psx/types.h"

extern u16 g_menu_input_disabled;
extern s32 g_current_event_thread_id;
extern s32 g_battle_event_input;
extern s32 g_unfiltered_battle_controller_input;
extern s32 D_8016D9B8;
extern u8 g_battle_thread_task_ids[];

/* Route controller input to the running battle event thread. */
void battle_route_event_input(void) {
    s32 thread;

    if (g_menu_input_disabled != 2) {
        return;
    }
    thread = g_current_event_thread_id;
    if (thread == 0) {
        return;
    }
    if (g_battle_event_input == 0) {
        D_8016D9B8 = 0;
    }
    if (*(s32*)(g_battle_thread_task_ids + thread * 1024) == 1) {
        g_battle_event_input = g_unfiltered_battle_controller_input;
    } else {
        g_battle_event_input = D_8016D9B8;
    }
}
