#include "psx/types.h"

extern s16 g_bunit_scroll_list_active;
extern s16 g_bunit_list_row_height;
extern s16 g_bunit_otag_index;
extern s16 g_bunit_semitrans_enabled;
extern u16 g_bunit_texture_page;
extern u16 g_bunit_clut_id;
extern s32 g_bunit_cursor_row;
extern s16 g_bunit_scroll_pixel_offset;
extern u8 g_bunit_sprite_color[];

extern void bunit_enqueue_textured_quad(s16* params, s32 a1, s32 a2, u8* a3, s32 a4, s32 a5, s32 a6, s32 a7);

u8* bunit_parse_draw_textured_quad(u8* cmd) {
    s16 params[4];
    s32 index;
    u8* table;

    if (g_bunit_scroll_list_active == 0) {
        index = cmd[4];
    } else {
        index = g_bunit_list_row_height * g_bunit_cursor_row + cmd[4] - g_bunit_scroll_pixel_offset;
        if (g_bunit_scroll_pixel_offset < 0) {
            index -= g_bunit_list_row_height;
        }
    }

    params[0] = cmd[3];
    params[1] = index;
    params[2] = cmd[5];
    params[3] = cmd[6];

    table = g_bunit_sprite_color;
    if (cmd[0] == 4) {
        table = 0;
    }

    bunit_enqueue_textured_quad(params, cmd[7], cmd[8], table, g_bunit_semitrans_enabled, g_bunit_texture_page, g_bunit_clut_id, g_bunit_otag_index);
    return cmd + cmd[1];
}
