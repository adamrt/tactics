#include "psx/types.h"

extern s32 get_script_variable(s32 index);
extern s32 require_apply_permanent_brave_faith_changes_and_collect_warnings(void);
extern s32 battle_get_next_available_thread_id();
extern void initialize_event_thread(s32 id, void (*callback)(void));
extern void battle_store_thread_function_parameters(s32 id, s32 a, s32 b, s32 c);
extern void wait_for_event_thread(s32 id);
extern void stop_current_event_thread(void);
extern void require_fade_rgb_31_frames(s32, s32, s32);
extern void require_render_display_condition_special_cases_thread(void);
extern void text_character_handling_thread(void);
extern s32 g_battle_text_pointer_1;
extern s32 g_battle_text_pointer_2;
extern s32 g_battle_text_pointer_3;
extern s32 g_battle_text_pointer_6;
extern s32 g_require_text_offset_1;
extern s32 g_require_text_offset_2;
extern s32 g_require_text_offset_3;
extern s32 g_require_text_offset_6;
extern u8 g_require_text_data[];
extern s32 g_require_affected_unit_count;
extern s32 g_require_affected_battle_unit_indices[];
extern s32 g_require_affected_unit_message_ids[];
extern s32 g_require_affected_unit_message_args[];
extern s32 g_text_substitution_value_0;

void require_apply_permanent_brave_faith_changes(void) {
    s32 i;
    s32 main_thread;

    if (get_script_variable(0x1fe) != 0)
        stop_current_event_thread();
    if (require_apply_permanent_brave_faith_changes_and_collect_warnings() == 0)
        stop_current_event_thread();
    g_battle_text_pointer_1 = g_require_text_offset_1 + (s32)g_require_text_data;
    g_battle_text_pointer_2 = g_require_text_offset_2 + (s32)g_require_text_data;
    g_battle_text_pointer_3 = g_require_text_offset_3 + (s32)g_require_text_data;
    g_battle_text_pointer_6 = g_require_text_offset_6 + (s32)g_require_text_data;
    main_thread = battle_get_next_available_thread_id(0x10, g_require_text_data);
    initialize_event_thread(main_thread, require_render_display_condition_special_cases_thread);
    battle_store_thread_function_parameters(main_thread, 5, 0, 0);
    require_fade_rgb_31_frames(0xd, 0xd, 2);
    for (i = 0; i < g_require_affected_unit_count; i++) {
        s32 unit_thread = battle_get_next_available_thread_id(0x10);
        g_text_substitution_value_0 = g_require_affected_battle_unit_indices[i];
        initialize_event_thread(unit_thread, text_character_handling_thread);
        battle_store_thread_function_parameters(unit_thread, 0x1b,
            g_require_affected_unit_message_ids[i],
            g_require_affected_unit_message_args[i]);
        wait_for_event_thread(unit_thread);
    }
    battle_store_thread_function_parameters(main_thread, 0, 0, 2);
    wait_for_event_thread(main_thread);
    require_fade_rgb_31_frames(6, 5, 2);
    stop_current_event_thread();
}
