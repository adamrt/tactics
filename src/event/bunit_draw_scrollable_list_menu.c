#include "psx/gpu.h"
#include "psx/types.h"

extern s16 g_bunit_list_visible_rows;
extern u16 g_bunit_list_row_height;
extern s16 D_801ec8c4;
extern u8 D_801ec8d4;
extern u16* g_bunit_list_entries;
extern u16* g_bunit_list_text_table;
extern u16 g_bunit_list_vram_width;
extern u8 D_801ec8ec;
extern u8 D_801ec8f0;
extern u8 D_801ec8f8;
extern s16 g_bunit_list_selected_index;
extern s16 g_bunit_scroll_base_index;
extern s16 g_bunit_list_entry_count;

extern void bunit_render_text_id_rows_to_vram(u16* arg0, s16* arg1, RECT* arg2, s32 arg3);

/* Find the list-geometry command (0x10) in the render stream, clamp the
 * selection and scroll window to it, and render the visible entries' text ids
 * into VRAM. */
void bunit_draw_scrollable_list_menu(u8* script) {
    RECT rect;
    s16 columns[20];
    s32 i;
    s16 visible_rows;
    s16 entry_count;
    s16 selected;

    while (script[0] != 0x10) {
        if (script[0] == 0x1c) {
            return;
        }
        script += script[1];
    }

    D_801ec8c4 = script[4];
    g_bunit_list_row_height = script[5];
    visible_rows = script[6];
    g_bunit_list_visible_rows = visible_rows;
    D_801ec8ec = script[9];
    D_801ec8f0 = script[10];
    g_bunit_list_vram_width = (D_801ec8ec * D_801ec8f0) >> 2;

    entry_count = g_bunit_list_entry_count;
    if (g_bunit_list_selected_index >= entry_count) {
        g_bunit_list_selected_index = entry_count - 1;
    }
    selected = g_bunit_list_selected_index;
    if (selected - g_bunit_scroll_base_index >= visible_rows) {
        g_bunit_scroll_base_index = selected;
    }
    if (selected < g_bunit_scroll_base_index) {
        g_bunit_scroll_base_index = selected;
    }
    if (entry_count < visible_rows) {
        g_bunit_scroll_base_index = 0;
    } else if (entry_count - g_bunit_scroll_base_index < visible_rows) {
        g_bunit_scroll_base_index = entry_count - visible_rows;
    }

    if (g_bunit_list_selected_index >= g_bunit_list_entry_count) {
        g_bunit_list_selected_index = g_bunit_list_entry_count - 1;
    }

    if (g_bunit_list_text_table != 0) {
        rect.x = 0x100;
        rect.y = 0x30;
        rect.w = g_bunit_list_vram_width;
        rect.h = (s32)g_bunit_list_visible_rows * 16;
        ClearImage(&rect, 0, 0, 0);
        for (i = 0; i < g_bunit_list_visible_rows; i++) {
            columns[i] = g_bunit_list_entries[i + g_bunit_scroll_base_index];
        }
        columns[i] = -1;
        rect.x = 0x100;
        rect.y = 0x30;
        rect.w = g_bunit_list_vram_width;
        rect.h = g_bunit_list_row_height;
        bunit_render_text_id_rows_to_vram(g_bunit_list_text_table, columns, &rect, 0);
    }

    D_801ec8f8 = 0;
    D_801ec8d4 = 0;
}
