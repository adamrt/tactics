#include "psx/types.h"

extern s16* g_jobstts_list_entries;
extern s32 D_801FA6F0;
extern s16 g_jobstts_list_entry_count;
extern s16 g_jobstts_list_selected_index;
extern s16 g_jobstts_scroll_base_index;
extern u8 g_jobstts_text_color[3];
extern s16 g_jobstts_otag_index;
extern s16 g_jobstts_list_row_rendering;
extern s16 g_jobstts_list_scroll_offset_y;
extern s8 D_801FA6E4;
extern s8 g_jobstts_transition_frame;

void jobstts_init_scrollable_list_menu_core(s16* entries, s32 selected_index, s32 data) {
    g_jobstts_list_entries = entries;
    D_801FA6F0 = data;
    if (entries != 0) {
        s32 first = *entries;
        g_jobstts_list_entry_count = 0;
        if (first != -1) {
            do {
                g_jobstts_list_entry_count = g_jobstts_list_entry_count + 1;
            } while (entries[g_jobstts_list_entry_count] != -1);
        }
    }
    g_jobstts_list_selected_index = selected_index;
    if (selected_index == 0) {
        g_jobstts_scroll_base_index = 0;
    }
    g_jobstts_text_color[0] = 0x80;
    g_jobstts_text_color[1] = 0x80;
    g_jobstts_text_color[2] = 0x80;
    g_jobstts_otag_index = 0;
    g_jobstts_list_row_rendering = 0;
    g_jobstts_list_scroll_offset_y = 0;
    D_801FA6E4 = 1;
    g_jobstts_transition_frame = 0;
}
