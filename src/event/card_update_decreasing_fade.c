#include "psx/gpu.h"
#include "psx/types.h"

extern u8 g_card_decreasing_fade_active;
extern s16 g_card_fade_intensity;
extern u8 g_card_fade_color[3];
extern u8 g_card_fade_color_g;
extern u8 g_card_fade_color_b;
extern RECT g_card_fade_rect;
extern u16 g_card_otag_length;
extern s32 card_get_event_speed(void);
extern void card_set_draw_mode_and_link_ot(s32, s32, s32, RECT*, s32);
extern void card_enqueue_translucent_tile(const RECT*, const u8*, s32, s32);

s32 card_update_decreasing_fade(void) {
    s32 result = 1;
    s32 speed = card_get_event_speed();

    if (g_card_decreasing_fade_active != 0) {
        g_card_fade_intensity -= speed * 8;
        if (g_card_fade_intensity <= 0) {
            g_card_decreasing_fade_active = 0;
            result = 0;
        }
        card_set_draw_mode_and_link_ot(
            0, 0, GetTPage(0, 2, 0x100, 0) & 0xffff, 0,
            g_card_otag_length - 2);
        g_card_fade_color_b = g_card_fade_intensity;
        g_card_fade_color_g = g_card_fade_intensity;
        g_card_fade_color[0] = g_card_fade_intensity;
        card_enqueue_translucent_tile(
            &g_card_fade_rect, g_card_fade_color, 1,
            g_card_otag_length - 1);
    }
    return result;
}
