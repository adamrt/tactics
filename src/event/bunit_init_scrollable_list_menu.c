#include "psx/types.h"

extern void bunit_init_scrollable_list_menu_core(s32 entries, s32 selected_index, s32 text_table);
extern s16 g_bunit_scroll_base_index;

void bunit_init_scrollable_list_menu(s32 entries, s32 selected_index, s16 scroll_base_index, s32 text_table) {
    bunit_init_scrollable_list_menu_core(entries, selected_index, text_table);
    g_bunit_scroll_base_index = scroll_base_index;
}
