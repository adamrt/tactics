#include "psx/types.h"

extern u8* g_event_threads;
extern s16 g_require_selection_result;
extern void switch_to_next_event_thread(void);
extern void battle_store_thread_function_parameters(s32, s32, s32, s32);
extern void wait_for_event_thread(s32 thread_id);

void require_wait_for_selection_menu_threads(void) {
    if (*(s32*)(g_event_threads + 0x1448) != 0) {
        s32 negative_result = -1;
        s32 positive_result = 1;

    wait_for_selection: {
        s32 selection = g_require_selection_result;

        if (selection == negative_result)
            goto selection_finished;
        if (selection == positive_result)
            goto selection_finished;
        if (selection == 0)
            goto selection_finished;
    }

        switch_to_next_event_thread();
        if (*(s32*)(g_event_threads + 0x1448) != 0)
            goto wait_for_selection;
    }

selection_finished:
    switch_to_next_event_thread();
    *(s32*)(g_event_threads + 0x1c4c) = 3;
    battle_store_thread_function_parameters(7, 0, 0, 2);
    wait_for_event_thread(7);
    wait_for_event_thread(5);
}
