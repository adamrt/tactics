#include "psx/types.h"

extern s16 g_equip_list_row_mode;
extern s32 (*g_equip_list_row_callbacks[])(s32);
extern s16 g_equip_scroll_base_index;
extern s32 g_equip_list_row_index;
extern s16 g_equip_list_scroll_offset;
extern u8* (*g_equip_sprite_command_handlers[])(u8*);

u8* equip_parse_conditional_block(u8* p) {
    s32 (*handler)(s32);
    s32 count;
    s32 arg;

    handler = g_equip_list_row_callbacks[p[3]];
    count = p[4];
    if (g_equip_list_row_mode == 0) {
        arg = p[5];
    } else {
        arg = g_equip_scroll_base_index + g_equip_list_row_index;
        if (g_equip_list_scroll_offset < 0) {
            arg = arg - 1;
        }
    }

    p += p[1];
    if (handler(arg) == 0) {
        count--;
        while (count != -1) {
            p += p[1];
            count--;
        }
        return p;
    }
    count--;
    while (count != -1) {
        p = g_equip_sprite_command_handlers[p[0]](p);
        count--;
    }
    return p;
}
