#include "psx/types.h"

extern s32 bunit_get_event_speed(void);
extern u32 func_8002398C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void bunit_enqueue_draw_mode(s32 a0, s32 a1, u32 a2, s32 a3, s32 a4);
extern void bunit_enqueue_translucent_tile(void* a0, void* a1, s32 a2, s32 a3);

extern u8 g_bunit_decreasing_fade_active;
extern s16 g_bunit_fade_intensity;
extern u16 g_bunit_otag_count;
extern u8 g_bunit_fade_rect[];

extern u8 g_bunit_fade_color[3];
extern u8 g_bunit_fade_color_g;
extern u8 g_bunit_fade_color_b;

s32 bunit_update_decreasing_fade(void) {
    s32 ret = 1;
    s32 speed = bunit_get_event_speed();

    if (g_bunit_decreasing_fade_active != 0) {
        g_bunit_fade_intensity -= speed * 8;
        if (g_bunit_fade_intensity <= 0) {
            g_bunit_decreasing_fade_active = 0;
            ret = 0;
        }
        bunit_enqueue_draw_mode(0, 0, func_8002398C(0, 2, 0x100, 0) & 0xFFFF, 0, g_bunit_otag_count - 2);
        {
            u8* p = g_bunit_fade_color;
            g_bunit_fade_color_b = g_bunit_fade_intensity;
            g_bunit_fade_color_g = g_bunit_fade_intensity;
            *p = g_bunit_fade_intensity;
            bunit_enqueue_translucent_tile(g_bunit_fade_rect, p, 1, g_bunit_otag_count - 1);
        }
    }
    return ret;
}
