#include "psx/types.h"

extern s32 battle_get_next_available_thread_id(s32 priority);
extern void initialize_event_thread(s32 thread_id, void (*function)(void));
extern void battle_store_thread_function_parameters(s32 thread_id, s32 arg0, s32 arg1,
    s32 arg2);
extern void require_wait_frames_or_skip_input(s32 frames);
extern void wait_for_event_thread(s32 thread_id);
extern void stop_current_event_thread(void);
extern void battle_refresh_hovered_unit_stats_display(void);

void require_display_ready_condition_bugged(void) {
    s32 thread_id = battle_get_next_available_thread_id(0x10);

    initialize_event_thread(thread_id, battle_refresh_hovered_unit_stats_display);
    battle_store_thread_function_parameters(thread_id, 0, 0, 0);
    require_wait_frames_or_skip_input(0x3c);
    battle_store_thread_function_parameters(thread_id, 0, 0, 1);
    wait_for_event_thread(thread_id);
    stop_current_event_thread();
}
