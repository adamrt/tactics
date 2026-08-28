#include "psx/types.h"

extern s16 g_bunit_scroll_list_active;
extern s16 g_bunit_scroll_base_index;
extern s16 g_bunit_scroll_pixel_offset;
extern s32 g_bunit_cursor_row;
extern s32 (*g_bunit_row_callbacks[])(s32);
extern u8* (*g_bunit_render_command_handlers[])(u8*);

/* Run the next `count` commands only if row callback cmd[3] returns nonzero
 * for the row (literal cmd[5], or the scroll cursor row when the scroll list
 * is active); otherwise skip them. */
u8* bunit_parse_if_row_callback(u8* cmd) {
    s32 (*callback)(s32);
    s32 count;
    s32 row;

    callback = g_bunit_row_callbacks[cmd[3]];
    count = cmd[4];
    if (g_bunit_scroll_list_active == 0) {
        row = cmd[5];
    } else {
        row = g_bunit_scroll_base_index + g_bunit_cursor_row;
        if (g_bunit_scroll_pixel_offset < 0) {
            row -= 1;
        }
    }
    cmd += cmd[1];
    if (callback(row) == 0) {
        while (--count != -1) {
            cmd += cmd[1];
        }
    } else {
        while (--count != -1) {
            cmd = g_bunit_render_command_handlers[cmd[0]](cmd);
        }
    }
    return cmd;
}
