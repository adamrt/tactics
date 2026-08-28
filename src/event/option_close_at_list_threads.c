#include "psx/types.h"

extern s16 g_option_menu_open;
extern s16 g_option_submenu_state;
extern s16 g_option_transition_timer;
extern u16 g_option_transition_finished;
extern u16 g_option_transition_duration;
extern s32 g_current_event_thread_id;
extern void* g_menu_text_pointer;

extern u8 g_option_at_list_text[];
extern void mark_thread_stopped(s32 thread_id);
extern void mark_thread_running(s32 thread_id);
extern void switch_to_next_event_thread(void);
extern void wait_for_event_thread(s32 thread_id);
extern void stop_current_event_thread(void);
extern void store_unit_names_and_event_block_data(s32, s32, s32);

/* Close the AT list's worker set and restore the parent option threads. */
void option_close_at_list_threads(void) {
    g_option_menu_open = 1;
    g_option_submenu_state = 2;

    mark_thread_stopped(g_current_event_thread_id + 1);
    mark_thread_stopped(g_current_event_thread_id + 2);
    mark_thread_stopped(g_current_event_thread_id + 3);
    mark_thread_stopped(g_current_event_thread_id + 4);

    while ((g_option_transition_timer = g_option_transition_duration + 100),
        g_option_transition_finished == 0) {
        switch_to_next_event_thread();
    }

    g_option_transition_finished = 0;
    g_option_transition_timer = 0;
    store_unit_names_and_event_block_data(0, 0xff, 0xff);

    wait_for_event_thread(13);
    wait_for_event_thread(12);
    wait_for_event_thread(11);
    wait_for_event_thread(10);

    g_menu_text_pointer = g_option_at_list_text;
    mark_thread_running(g_current_event_thread_id + 1);
    mark_thread_running(g_current_event_thread_id + 2);
    mark_thread_running(g_current_event_thread_id + 3);
    mark_thread_running(g_current_event_thread_id + 4);

    g_option_menu_open = 0;
    g_option_submenu_state = 0;
    stop_current_event_thread();
}
