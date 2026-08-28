#include "psx/types.h"

extern s32 (*g_call_inner_subroutine_target)();
extern s32 get_script_variable(s32 index);
extern s32 call_inner_subroutine();
extern s32 battle_get_next_available_thread_id(s32 type);
extern void initialize_event_thread(s32 id, void (*callback)(void));
extern void battle_store_thread_function_parameters(s32 id, s32 a, s32 b, s32 c);
extern void wait_for_event_thread(s32 id);
extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);
extern void wait_frames(s32 frames);
extern void require_wait_frames_or_skip_input(s32 frames);
extern void main_unload_scenario_music_and_tunes(void);
extern s32 main_open_scenario_smd_files(s32 value);
extern s32 main_poll_scenario_smd_file_load(void);
extern s32 switch_music_track(s32 slot, s32 volume, s32 time);
extern void require_render_display_condition_special_cases_thread(void);

void require_show_battle_congratulations_messages(void) {
    s32 thread_a;
    s32 thread_b;

    g_call_inner_subroutine_target = main_unload_scenario_music_and_tunes;
    call_inner_subroutine();
    g_call_inner_subroutine_target = main_open_scenario_smd_files;
    call_inner_subroutine(get_script_variable(0x27) != 0x145 ? 0x2b : 0x2c);
    do {
        switch_to_next_event_thread();
        g_call_inner_subroutine_target = main_poll_scenario_smd_file_load;
    } while (call_inner_subroutine() != 0);
    g_call_inner_subroutine_target = switch_music_track;
    call_inner_subroutine(1, 0x7f, 0);

    thread_a = battle_get_next_available_thread_id(0x10);
    initialize_event_thread(thread_a, require_render_display_condition_special_cases_thread);
    battle_store_thread_function_parameters(thread_a, 1, 0, 0);
    if (get_script_variable(0x27) != 0x145)
        require_wait_frames_or_skip_input(0x1e);
    else
        wait_frames(0x1e);

    thread_b = battle_get_next_available_thread_id(0x10);
    initialize_event_thread(thread_b, require_render_display_condition_special_cases_thread);
    battle_store_thread_function_parameters(thread_b, 7, 1, 0);
    if (get_script_variable(0x27) != 0x145)
        require_wait_frames_or_skip_input(0xb4);
    else
        wait_frames(0x12c);

    battle_store_thread_function_parameters(thread_a, 0, 0, 2);
    battle_store_thread_function_parameters(thread_b, 0, 0, 2);
    wait_for_event_thread(thread_a);
    wait_for_event_thread(thread_b);
    stop_current_event_thread();
}
