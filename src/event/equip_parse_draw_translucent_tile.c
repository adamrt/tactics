#include "psx/types.h"

extern s16 g_equip_list_row_mode;
extern s16 g_equip_list_row_height;
extern s32 g_equip_list_row_index;
extern s16 g_equip_list_scroll_offset;
extern u8 g_equip_semitransparency;
extern s16 g_equip_sprite_ot_index;

extern void equip_enqueue_translucent_tile(s16* rect, u8* data, u8 semitransparency, s16 ot_index);

u8* equip_parse_draw_translucent_tile(u8* cmd) {
    s16 rect[4];
    s32 y;
    s32 base;

    if (g_equip_list_row_mode == 0) {
        y = cmd[3];
    } else {
        base = g_equip_list_row_height * g_equip_list_row_index + cmd[3];
        y = base + g_equip_list_scroll_offset;
        if (g_equip_list_scroll_offset < 0) {
            y = y - g_equip_list_row_height;
        }
    }
    rect[0] = cmd[2];
    rect[1] = y;
    rect[2] = cmd[4];
    rect[3] = cmd[5];
    equip_enqueue_translucent_tile(rect, cmd + 6, g_equip_semitransparency, g_equip_sprite_ot_index);
    return cmd + cmd[1];
}
