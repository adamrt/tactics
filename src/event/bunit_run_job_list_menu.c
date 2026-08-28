#include "psx/types.h"

extern u8 g_bunit_job_list_initialized;
extern s16 g_bunit_job_ids[];
extern s16 g_bunit_selected_unit_index;
extern s16 g_bunit_list_selected_index;
extern s32 g_bunit_menu_input_active_mask;
extern s32 g_bunit_selection_text_id;
extern s8 g_bunit_menu_state;
extern s32 D_801CF454;
extern s16 g_bunit_selected_job_id;
extern s16 g_bunit_selected_job_generic_index;
extern s16 g_bunit_scroll_base_index;
extern s32 g_battle_text_pointer_6;
extern s32 g_event_mode;
extern s32 D_801E3470;

extern void* g_bunit_row_callbacks;
extern void* g_bunit_row_callback_2;
extern void* g_bunit_row_callback_5;
extern void* g_bunit_row_callback_6;
extern void* g_bunit_row_callback_13;

extern void bunit_set_event_speed(s32 speed);
extern s32 bunit_calculate_unit_jobs(s32 unit_id, s16* job_ids, s32 arg2);
extern void bunit_lookup_indexed_action_record(s32 index, s16* out_a, s16* out_b, s16* list);
extern void bunit_init_scrollable_list_menu(s16* list, s32 a1, s16 a2, s32 a3);
extern void bunit_set_indexed_action_record(s32 index, s32 field0, s32 field2, s16* lookup);
extern void bunit_dispatch_menu_with_override(s32* menu, s32 state, s32 override);
extern s32 bunit_get_generic_job_index(s32 job_id);
extern s32 bunit_refresh_current_job_level(s32 index);
extern s32 bunit_refresh_current_job_jp(s32 index);
extern s32 bunit_refresh_current_job_total_jp(s32 index);
extern s32 bunit_refresh_next_job_level_jp_requirement(s32 index);
extern s32 bunit_refresh_current_job_mastered(s32 index);

s32 bunit_run_job_list_menu(void) {
    s16 out_a;
    s16 out_b;
    s32 mask;

    if (g_bunit_job_list_initialized == 0) {
        bunit_set_event_speed(2);
        bunit_calculate_unit_jobs((u8)g_bunit_selected_unit_index, g_bunit_job_ids, 0);
        g_bunit_row_callbacks = (void*)bunit_refresh_current_job_level;
        g_bunit_row_callback_2 = (void*)bunit_refresh_current_job_jp;
        g_bunit_row_callback_5 = (void*)bunit_refresh_next_job_level_jp_requirement;
        g_bunit_row_callback_6 = (void*)bunit_refresh_current_job_total_jp;
        g_bunit_row_callback_13 = (void*)bunit_refresh_current_job_mastered;
        bunit_lookup_indexed_action_record(9, &out_a, &out_b, g_bunit_job_ids);
        bunit_init_scrollable_list_menu(g_bunit_job_ids, out_a, out_b, g_battle_text_pointer_6);
        g_bunit_job_list_initialized = 1;
    }

    g_bunit_selection_text_id = g_bunit_job_ids[g_bunit_list_selected_index] + 0x6000;
    mask = g_bunit_menu_input_active_mask;
    if (mask & 0x40) {
        bunit_set_event_speed(0);
        g_bunit_menu_state = 2;
        g_bunit_job_list_initialized = 0;
        return -1;
    }
    if ((mask & 0x20) && D_801CF454 == 2) {
        g_bunit_selected_job_id = g_bunit_job_ids[g_bunit_list_selected_index];
        g_bunit_selected_job_generic_index = bunit_get_generic_job_index(g_bunit_selected_job_id);
        bunit_refresh_current_job_level(g_bunit_list_selected_index);
        bunit_refresh_current_job_jp(g_bunit_list_selected_index);
        bunit_refresh_current_job_total_jp(g_bunit_list_selected_index);
        bunit_refresh_next_job_level_jp_requirement(g_bunit_list_selected_index);
        bunit_set_indexed_action_record(9, g_bunit_list_selected_index, g_bunit_scroll_base_index, g_bunit_job_ids);
        g_bunit_job_list_initialized = 0;
        g_bunit_menu_state = 1;
        return 1;
    }
    bunit_dispatch_menu_with_override(&D_801E3470, g_bunit_menu_input_active_mask, g_event_mode);
    return 0;
}
