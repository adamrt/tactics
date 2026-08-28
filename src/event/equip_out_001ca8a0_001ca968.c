#include "psx/types.h"

extern s16* D_801E9024;
extern s32 D_801E9028;
extern s16 g_equip_list_entry_count;
extern s16 D_801E90F8;
extern s16 g_equip_scroll_base_index;
extern u8 g_equip_sprite_color;
extern u8 g_equip_sprite_color_g;
extern u8 g_equip_sprite_color_b;
extern s16 g_equip_sprite_ot_index;
extern s16 g_equip_list_row_mode;
extern s16 g_equip_list_scroll_offset;
extern u8 D_801E901C;
extern u8 g_equip_transition_frame;
extern u8 g_equip_zoom_draw_area_active;

/* Point the scrollable list menu at a new -1 terminated entry list and reset
   its render state. */
void equip_init_scrollable_list_menu_core(s16* entries, s32 keep_scroll, s32 arg2) {
    D_801E9024 = entries;
    D_801E9028 = arg2;

    if (entries != 0) {
        g_equip_list_entry_count = 0;
        while (entries[g_equip_list_entry_count] != -1) {
            g_equip_list_entry_count = g_equip_list_entry_count + 1;
        }
    }

    D_801E90F8 = keep_scroll;
    if (keep_scroll == 0) {
        g_equip_scroll_base_index = 0;
    }

    g_equip_sprite_color = 0x80;
    g_equip_sprite_color_g = 0x80;
    g_equip_sprite_color_b = 0x80;
    g_equip_sprite_ot_index = 0;
    g_equip_list_row_mode = 0;
    g_equip_list_scroll_offset = 0;
    D_801E901C = 1;
    g_equip_transition_frame = 0;
    g_equip_zoom_draw_area_active = 0;
}
