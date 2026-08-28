#include "psx/gpu.h"
#include "psx/types.h"

extern u8 g_card_text_color[3];
extern s16 g_card_text_otag_index;
extern s16 g_card_draw_semitrans;
extern u16 g_card_texture_page;
extern u16 g_card_draw_clut;
extern void card_enqueue_textured_quad(RECT* rect, s32 u, s32 v,
    const u8* color, s32 semitrans,
    s32 texture_page, s32 clut,
    s32 otag_index);

u8* card_parse_draw_textured_quad(u8* command) {
    RECT rect;
    const u8* color;
    s32 x;
    s32 y;

    x = command[3];
    y = command[4];
    rect.x = x;
    rect.y = y;
    rect.w = command[5];
    rect.h = command[6];
    color = g_card_text_color;
    if (command[0] == 4) {
        color = 0;
    }
    card_enqueue_textured_quad(&rect, command[7], command[8], color,
        g_card_draw_semitrans, g_card_texture_page,
        g_card_draw_clut, g_card_text_otag_index);
    return command + command[1];
}
