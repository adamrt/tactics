#include "psx/types.h"

extern s16 g_equip_list_row_mode;
extern s16 g_equip_scroll_base_index;
extern s32 g_equip_list_row_index;
extern s16 g_equip_list_scroll_offset;
extern s32 (*g_equip_list_row_callbacks[])(s32);
extern u8* (*g_equip_sprite_command_handlers[])(u8*);

u8* equip_parse_if_else_block(u8* p) {
    s32 a;
    s32 b;
    s32 (*handler)(s32);
    s32 idx;

    a = p[4];
    b = p[5];
    handler = g_equip_list_row_callbacks[p[3]];
    if (g_equip_list_row_mode == 0) {
        idx = p[6];
    } else {
        idx = g_equip_scroll_base_index + g_equip_list_row_index;
        if (g_equip_list_scroll_offset < 0) {
            idx--;
        }
    }
    p += p[1];
    if (handler(idx) != 0) {
        for (a--; a != -1; a--) {
            p = g_equip_sprite_command_handlers[*p](p);
        }
        for (b--; b != -1; b--) {
            p += p[1];
        }
    } else {
        for (a--; a != -1; a--) {
            p += p[1];
        }
        for (b--; b != -1; b--) {
            p = g_equip_sprite_command_handlers[*p](p);
        }
    }
    return p;
}
