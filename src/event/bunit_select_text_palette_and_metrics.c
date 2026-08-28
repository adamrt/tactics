#include "psx/types.h"

extern s8 D_801EC8F4;
extern u8 g_bunit_sprite_color;
extern u8 g_bunit_sprite_color_g;
extern u8 g_bunit_sprite_color_b;
extern u16 D_801ECAE4;
extern u16 D_801ECA94;
extern u16 D_801ECA78;
extern u16 D_801ECA30;
extern u16 D_801ECAF0;
extern u16 D_801ECB5C;
extern u16 D_801CF960;
extern u16 D_801CF962;
extern u16 D_801CF964;
extern u16 D_801CF966;
extern u16 D_801CF968;
extern u16 D_801CF96A;
extern u16 D_801CF96E;
extern u16 D_801CF970;
extern u16 D_801CF972;
extern u16 D_801CF974;
extern u16 D_801CF984;
extern u16 D_801CF986;

void bunit_select_text_palette_and_metrics(s32 mode) {
    /* Pins + the fence below: the target loads all six metrics into
     * $v1,$a0..$a3,$t0 in declaration order *before* the two colour byte
     * stores. Unpinned, GCC allocates the six in reverse order and the
     * scheduler hoists the `sb`s above the `lhu`s (same as the card twin). */
    u16 metric_0;
    register u16 metric_1 __asm__("$4");
    register u16 metric_2 __asm__("$5");
    register u16 metric_3 __asm__("$6");
    register u16 metric_4 __asm__("$7");
    register u16 metric_5 __asm__("$8");
    u8 color;

    D_801EC8F4 = mode;
    color = 0x60;
    if (mode != 0) {
        metric_0 = D_801CF984;
        metric_1 = D_801CF964;
        metric_2 = D_801CF962;
        metric_3 = D_801CF96A;
        metric_4 = D_801CF972;
        metric_5 = D_801CF974;
        __asm__("" : : "r"(metric_0), "r"(metric_1), "r"(metric_2),
            "r"(metric_3), "r"(metric_4), "r"(metric_5));
        g_bunit_sprite_color = color;
        g_bunit_sprite_color_g = color;
        color = 0x80;
    } else {
        metric_0 = D_801CF986;
        metric_1 = D_801CF966;
        metric_2 = D_801CF960;
        metric_3 = D_801CF968;
        metric_4 = D_801CF96E;
        metric_5 = D_801CF970;
        color = 0x80;
        g_bunit_sprite_color = color;
        g_bunit_sprite_color_g = color;
    }
    g_bunit_sprite_color_b = color;
    D_801ECAE4 = metric_0;
    D_801ECA94 = metric_1;
    D_801ECA78 = metric_2;
    D_801ECA30 = metric_3;
    D_801ECAF0 = metric_4;
    D_801ECB5C = metric_5;
}
