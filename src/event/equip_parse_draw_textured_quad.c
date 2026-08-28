#include "psx/types.h"

extern s16 g_equip_list_row_mode;
extern s16 g_equip_list_row_height;
extern s32 g_equip_list_row_index;
extern s16 g_equip_list_scroll_offset;
extern u8 g_equip_sprite_color[];
extern s16 g_equip_sprite_ot_index;
extern s16 g_equip_semitransparency;
extern u16 g_equip_texture_page;
extern u16 g_equip_clut_id;

extern void equip_enqueue_textured_quad(s16* rect, s32 arg1, s32 arg2, u8* color, s32 arg4,
    s32 arg5, s32 arg6, s32 arg7);

u8* equip_parse_draw_textured_quad(u8* cmd) {
    s16 rect[4];
    s32 y;
    u8* color;

    if (g_equip_list_row_mode == 0) {
        y = cmd[4];
    } else {
        y = g_equip_list_row_height * g_equip_list_row_index + cmd[4] - g_equip_list_scroll_offset;
        if (g_equip_list_scroll_offset < 0) {
            y -= g_equip_list_row_height;
        }
    }

    rect[0] = cmd[3];
    rect[1] = y;
    rect[2] = cmd[5];
    rect[3] = cmd[6];

    color = g_equip_sprite_color;
    if (cmd[0] == 4) {
        color = 0;
    }

    equip_enqueue_textured_quad(rect, cmd[7], cmd[8], color, g_equip_semitransparency, g_equip_texture_page,
        g_equip_clut_id, g_equip_sprite_ot_index);
    return cmd + cmd[1];
}
