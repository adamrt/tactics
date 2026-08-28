#include "psx/types.h"

extern s8 g_equip_zoom_draw_area_active;
extern s16 g_equip_sprite_ot_index;
extern void func_801CA648(s16* rect, s32 otag);

/* Stream command: enqueue a draw-area rect (x, y, w, h from the command)
   unless the zoom transition already emitted one. */
u8* equip_parse_set_draw_area(u8* cmd) {
    s16 rect[4];

    if (g_equip_zoom_draw_area_active == 0) {
        rect[0] = cmd[2];
        rect[1] = cmd[3];
        rect[2] = cmd[4];
        rect[3] = cmd[5];
        func_801CA648(rect, g_equip_sprite_ot_index - 1);
    }
    return cmd + cmd[1];
}
