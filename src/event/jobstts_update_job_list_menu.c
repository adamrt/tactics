#include "psx/types.h"

typedef void (*JobsttsMenuFn)();

extern JobsttsMenuFn g_jobstts_render_command_conditions[];
extern s16 g_jobstts_job_ids[];
extern s32 g_jobstts_job_list_menu_initialized;
extern s16 g_jobstts_list_selected_index;
extern s16 g_jobstts_scroll_base_index;
extern s32 g_jobstts_input_primary_repeat;
extern s32 g_jobstts_selected_job_text_id;
extern u16 g_jobstts_selected_job_id;
extern u8 g_jobstts_menu_state;
extern u8 g_jobstts_job_list_render_commands[];
extern s32 g_event_mode;
extern void* g_battle_text_pointer_6;

extern void jobstts_refresh_current_job_level(s32 index);
extern void jobstts_refresh_current_job_jp(s32 index);
extern void jobstts_refresh_current_job_total_jp(s32 index);
extern s32 jobstts_refresh_current_job_mastered(s32 index);
extern void jobstts_refresh_next_job_level_jp_requirement(s32 index);
extern void func_801E01B4(s32 arg0, s16* arg1, s32 arg2);
extern void jobstts_load_ability_selection_state(s32 arg0, s16* arg1, s16* arg2, s16* arg3);
extern void jobstts_init_scrollable_list_menu(s16* arg0, s32 arg1, s32 arg2, void* arg3);
extern void jobstts_store_ability_selection_state(s32 arg0, s32 arg1, s32 arg2, s16* arg3);
extern void jobstts_set_mode_and_render_command_stream(u8* arg0, s32 arg1, s32 arg2);

s32 jobstts_update_job_list_menu(void) {
    s16 state[10];
    s32 input;

    if (g_jobstts_job_list_menu_initialized == 0) {
        g_jobstts_render_command_conditions[0] = (JobsttsMenuFn)jobstts_refresh_current_job_level;
        g_jobstts_render_command_conditions[2] = (JobsttsMenuFn)jobstts_refresh_current_job_jp;
        g_jobstts_render_command_conditions[5] = (JobsttsMenuFn)jobstts_refresh_next_job_level_jp_requirement;
        g_jobstts_render_command_conditions[6] = (JobsttsMenuFn)jobstts_refresh_current_job_total_jp;
        g_jobstts_render_command_conditions[13] = (JobsttsMenuFn)jobstts_refresh_current_job_mastered;
        func_801E01B4(0, g_jobstts_job_ids, 0);
        jobstts_load_ability_selection_state(4, &state[8], &state[9], g_jobstts_job_ids);
        jobstts_init_scrollable_list_menu(g_jobstts_job_ids, state[8], state[9], g_battle_text_pointer_6);
        g_jobstts_job_list_menu_initialized = 1;
    }

    g_jobstts_selected_job_text_id = g_jobstts_job_ids[g_jobstts_list_selected_index] + 0x6000;
    input = g_jobstts_input_primary_repeat;
    if (input & 0x20) {
        g_jobstts_selected_job_id = g_jobstts_job_ids[g_jobstts_list_selected_index];
        jobstts_refresh_current_job_level(g_jobstts_list_selected_index);
        jobstts_refresh_current_job_jp(g_jobstts_list_selected_index);
        jobstts_refresh_current_job_total_jp(g_jobstts_list_selected_index);
        if (jobstts_refresh_current_job_mastered(g_jobstts_list_selected_index) == 0) {
            jobstts_refresh_next_job_level_jp_requirement(g_jobstts_list_selected_index);
        }
        jobstts_store_ability_selection_state(4, g_jobstts_list_selected_index, g_jobstts_scroll_base_index, g_jobstts_job_ids);
        g_jobstts_job_list_menu_initialized = 0;
        g_jobstts_menu_state = 1;
        return 1;
    }
    jobstts_set_mode_and_render_command_stream(g_jobstts_job_list_render_commands, input, g_event_mode);
    return 0;
}
