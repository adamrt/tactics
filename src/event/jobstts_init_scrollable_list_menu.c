#include "psx/types.h"

extern void jobstts_init_scrollable_list_menu_core(const s16* entries,
    s32 selected_index,
    const void* data);
extern s16 g_jobstts_scroll_base_index;

void jobstts_init_scrollable_list_menu(const s16* entries, s32 selected_index,
    s32 value, const void* data) {
    jobstts_init_scrollable_list_menu_core(entries, selected_index, data);
    g_jobstts_scroll_base_index = value;
}
