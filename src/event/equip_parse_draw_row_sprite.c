#include "psx/types.h"

typedef u8* (*EquipRowFunc)(s32 row);

extern EquipRowFunc g_equip_list_row_callbacks[];
extern s16 g_equip_list_row_mode;
extern s16 g_equip_scroll_base_index;
extern s32 g_equip_list_row_index;
extern s16 g_equip_list_scroll_offset;
extern u8 g_equip_row_sprite_command_body[];
extern u16 g_equip_texture_page;
extern u16 g_equip_clut_id;

extern u8* equip_parse_draw_textured_quad(u8* cmd);

u8* equip_parse_draw_row_sprite(u8* cmd) {
    EquipRowFunc fn;
    u8* entry;
    s32 row;
    u16 tpage;
    u16 clut;

    fn = g_equip_list_row_callbacks[cmd[2]];
    if (g_equip_list_row_mode == 0) {
        row = cmd[3];
    } else {
        row = g_equip_scroll_base_index + g_equip_list_row_index;
        if (g_equip_list_scroll_offset < 0) {
            row--;
        }
    }

    entry = fn(row);
    if (entry != 0) {
        g_equip_row_sprite_command_body[0] = cmd[4];
        g_equip_row_sprite_command_body[1] = cmd[5];
        g_equip_row_sprite_command_body[2] = entry[4];
        g_equip_row_sprite_command_body[3] = entry[6];
        g_equip_row_sprite_command_body[4] = entry[0];
        g_equip_row_sprite_command_body[5] = entry[2];
        clut = *(u16*)(entry + 8);
        tpage = *(u16*)(entry + 0xa);
        g_equip_clut_id = clut;
        g_equip_texture_page = tpage;
        equip_parse_draw_textured_quad(g_equip_row_sprite_command_body - 3);
    }

    return cmd + cmd[1];
}
