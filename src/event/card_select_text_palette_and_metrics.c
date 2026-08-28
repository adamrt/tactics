#include "psx/types.h"

extern s8 g_card_layout_mode;
extern u8 g_card_text_color_r;
extern u8 g_card_text_color_g;
extern u8 g_card_text_color_b;
extern u16 g_card_metric_0;
extern u16 g_card_metric_1;
extern u16 g_card_metric_2;
extern u16 g_card_metric_3;
extern u16 g_card_metric_4;
extern u16 g_card_metric_5;
extern u16 D_801ca8a0;
extern u16 D_801ca8a2;
extern u16 D_801ca8a4;
extern u16 D_801ca8a6;
extern u16 D_801ca8a8;
extern u16 D_801ca8aa;
extern u16 g_card_cursor_mode0_foreground_clut;
extern u16 g_card_cursor_mode0_background_clut;
extern u16 g_card_cursor_mode1_foreground_clut;
extern u16 g_card_cursor_mode1_background_clut;
extern u16 D_801ca8c4;
extern u16 D_801ca8c6;

void card_select_text_palette_and_metrics(s32 mode) {
    /* Pins + the fence below: the target loads all six metrics into
     * $v1,$a0..$a3,$t0 in declaration order *before* the two colour byte
     * stores. Unpinned, GCC allocates the six in reverse order and the
     * scheduler hoists the `sb`s above the `lhu`s (verified: 12 insns move). */
    u16 metric_0;
    register u16 metric_1 __asm__("$4");
    register u16 metric_2 __asm__("$5");
    register u16 metric_3 __asm__("$6");
    register u16 metric_4 __asm__("$7");
    register u16 metric_5 __asm__("$8");
    u8 color;

    g_card_layout_mode = mode;
    color = 0x60;
    if (mode != 0) {
        metric_0 = D_801ca8c4;
        metric_1 = D_801ca8a4;
        metric_2 = D_801ca8a2;
        metric_3 = D_801ca8aa;
        metric_4 = g_card_cursor_mode1_foreground_clut;
        metric_5 = g_card_cursor_mode1_background_clut;
        __asm__("" : : "r"(metric_0), "r"(metric_1), "r"(metric_2),
            "r"(metric_3), "r"(metric_4), "r"(metric_5));
        g_card_text_color_r = color;
        g_card_text_color_g = color;
        color = 0x80;
    } else {
        metric_0 = D_801ca8c6;
        metric_1 = D_801ca8a6;
        metric_2 = D_801ca8a0;
        metric_3 = D_801ca8a8;
        metric_4 = g_card_cursor_mode0_foreground_clut;
        metric_5 = g_card_cursor_mode0_background_clut;
        color = 0x80;
        g_card_text_color_r = color;
        g_card_text_color_g = color;
    }
    g_card_text_color_b = color;
    g_card_metric_0 = metric_0;
    g_card_metric_1 = metric_1;
    g_card_metric_2 = metric_2;
    g_card_metric_3 = metric_3;
    g_card_metric_4 = metric_4;
    g_card_metric_5 = metric_5;
}
