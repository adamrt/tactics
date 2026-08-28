#include "psx/types.h"

/* Sprite record returned by a row callback; only the low byte of each
 * u16 coordinate is copied into the textured-quad command. */
typedef struct {
    u8 u;      /* 0x00 */
    u8 u_hi;   /* 0x01 */
    u8 v;      /* 0x02 */
    u8 v_hi;   /* 0x03 */
    u8 w;      /* 0x04 */
    u8 w_hi;   /* 0x05 */
    u8 h;      /* 0x06 */
    u8 h_hi;   /* 0x07 */
    u16 clut;  /* 0x08 */
    u16 tpage; /* 0x0A */
} BunitRowSprite;

extern s16 g_bunit_scroll_list_active;
extern s16 g_bunit_scroll_base_index;
extern s32 g_bunit_cursor_row;
extern s16 g_bunit_scroll_pixel_offset;
extern u16 g_bunit_texture_page;
extern u16 g_bunit_clut_id;
extern u8 g_bunit_row_quad_command[];
extern BunitRowSprite* (*g_bunit_row_callbacks[])(s32);

extern void bunit_parse_draw_textured_quad(u8* cmd);

u8* bunit_parse_draw_row_callback_quad(u8* cmd) {
    BunitRowSprite* entry;
    s32 row;
    BunitRowSprite* (*callback)(s32);

    callback = g_bunit_row_callbacks[cmd[2]];
    if (g_bunit_scroll_list_active == 0) {
        row = cmd[3];
    } else {
        row = g_bunit_scroll_base_index + g_bunit_cursor_row;
        if (g_bunit_scroll_pixel_offset < 0) {
            row -= 1;
        }
    }

    entry = callback(row);
    if (entry != 0) {
        g_bunit_row_quad_command[3] = cmd[4];
        g_bunit_row_quad_command[4] = cmd[5];
        g_bunit_row_quad_command[5] = entry->w;
        g_bunit_row_quad_command[6] = entry->h;
        g_bunit_row_quad_command[7] = entry->u;
        g_bunit_row_quad_command[8] = entry->v;
        g_bunit_clut_id = entry->clut;
        g_bunit_texture_page = entry->tpage;
        bunit_parse_draw_textured_quad(g_bunit_row_quad_command);
    }
    return cmd + cmd[1];
}
