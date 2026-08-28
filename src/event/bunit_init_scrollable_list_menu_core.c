#include "psx/types.h"

extern s16* g_bunit_list_entries;
extern s32 g_bunit_list_text_table;
extern u16 g_bunit_list_entry_count;
extern s16 g_bunit_list_selected_index;
extern s16 g_bunit_scroll_base_index;
extern u8 g_bunit_sprite_color;
extern u8 g_bunit_sprite_color_g;
extern u8 g_bunit_sprite_color_b;
extern s16 g_bunit_otag_index;
extern s16 g_bunit_scroll_list_active;
extern s16 g_bunit_scroll_pixel_offset;
extern u8 D_801EC8D4;
extern u8 g_bunit_transition_frame;
extern u8 g_bunit_otag_index_locked;
extern u8 D_801CF988;

void bunit_init_scrollable_list_menu_core(s16* entries, s32 selected_index, s32 text_table) {
    s32 first;

    g_bunit_list_entries = entries;
    g_bunit_list_text_table = text_table;
    if (entries != 0) {
        first = entries[0];
        g_bunit_list_entry_count = 0;
        if (first != -1) {
            do {
                g_bunit_list_entry_count = g_bunit_list_entry_count + 1;
            } while (entries[(s16)g_bunit_list_entry_count] != -1);
        }
    }
    g_bunit_list_selected_index = selected_index;
    if (selected_index == 0) {
        g_bunit_scroll_base_index = 0;
    }
    g_bunit_sprite_color = 0x80;
    g_bunit_sprite_color_g = 0x80;
    g_bunit_sprite_color_b = 0x80;
    g_bunit_otag_index = 0;
    g_bunit_scroll_list_active = 0;
    g_bunit_scroll_pixel_offset = 0;
    D_801EC8D4 = 1;
    g_bunit_transition_frame = 0;
    g_bunit_otag_index_locked = 0;
    D_801CF988 = 0;
}
