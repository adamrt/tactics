#include "psx/types.h"

extern void set_current_thread_task_id(s32 value);
extern s32 battle_get_first_thread_parameter(void);
extern s32 battle_get_second_thread_parameter(void);
extern s32 battle_get_next_available_thread_id(s32 type);
extern void initialize_event_thread(s32 id, void (*callback)(void));
extern void battle_store_thread_function_parameters(s32 id, s32 a, s32 b, s32 c);
extern void wait_for_event_thread(s32 id);
extern void stop_current_event_thread(void);
extern void require_wait_frames_or_skip_input(s32 frames);
extern void require_display_ready_condition_bugged(void);
extern void require_show_battle_congratulations_messages(void);
extern void require_render_gil_reward_ticker(void);
extern void require_render_war_trophies(void);
extern void require_apply_permanent_brave_faith_changes(void);
extern void require_remove_units_with_low_brave_or_high_faith(void);
extern void require_apply_post_battle_unit_changes(void);
extern void require_render_display_condition_general_cases(s32 value);
extern void require_render_display_condition_special_cases_thread(void);

void require_dispatch_display_condition(void) {
    s32 condition;
    s32 parameter;
    s32 thread;

    set_current_thread_task_id(0x38);
    condition = battle_get_first_thread_parameter();
    parameter = battle_get_second_thread_parameter();
    if (condition >= 8)
        require_render_display_condition_general_cases(parameter);
    thread = battle_get_next_available_thread_id(0x10);

    if (condition == 0) {
        initialize_event_thread(
            thread, require_render_display_condition_special_cases_thread);
        battle_store_thread_function_parameters(thread, 0, 0, 0);
        require_wait_frames_or_skip_input(parameter);
        battle_store_thread_function_parameters(thread, 0, 0, 2);
        wait_for_event_thread(thread);
        goto finished;
    }

    if (condition == 1)
        initialize_event_thread(thread, require_display_ready_condition_bugged);
    else if (condition == 2)
        initialize_event_thread(
            thread, require_show_battle_congratulations_messages);
    else if (condition == 3)
        initialize_event_thread(thread, require_render_gil_reward_ticker);
    else if (condition == 4)
        initialize_event_thread(thread, require_render_war_trophies);
    else if (condition == 5)
        initialize_event_thread(
            thread, require_apply_permanent_brave_faith_changes);
    else if (condition != 6)
        goto check_post_battle_changes;
    else
        initialize_event_thread(
            thread, require_remove_units_with_low_brave_or_high_faith);

    battle_store_thread_function_parameters(thread, 0, 0, 0);
    wait_for_event_thread(thread);
    goto finished;

check_post_battle_changes:
    if (condition == 7)
        require_apply_post_battle_unit_changes();
finished:
    stop_current_event_thread();
}
