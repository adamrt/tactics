#include "psx/types.h"

extern s8 D_801FA708;
extern u8 g_jobstts_text_color;
extern u8 g_jobstts_text_color_g;
extern u8 g_jobstts_text_color_b;
extern u16 D_801FA7E4;
extern u16 D_801FA7A8;
extern u16 D_801FA78C;
extern u16 D_801FA744;
extern u16 D_801FA7F0;
extern u16 D_801FA80C;
extern u16 D_801EFF74;
extern u16 D_801EFF76;
extern u16 D_801EFF78;
extern u16 D_801EFF7A;
extern u16 D_801EFF7C;
extern u16 D_801EFF7E;
extern u16 D_801EFF82;
extern u16 D_801EFF84;
extern u16 D_801EFF86;
extern u16 D_801EFF88;
extern u16 D_801EFF98;
extern u16 D_801EFF9A;

void jobstts_select_text_palette_and_metrics(s32 mode) {
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

    D_801FA708 = mode;
    color = 0x60;
    if (mode != 0) {
        metric_0 = D_801EFF98;
        metric_1 = D_801EFF78;
        metric_2 = D_801EFF76;
        metric_3 = D_801EFF7E;
        metric_4 = D_801EFF86;
        metric_5 = D_801EFF88;
        __asm__("" : : "r"(metric_0), "r"(metric_1), "r"(metric_2),
            "r"(metric_3), "r"(metric_4), "r"(metric_5));
        g_jobstts_text_color = color;
        g_jobstts_text_color_g = color;
        color = 0x80;
    } else {
        metric_0 = D_801EFF9A;
        metric_1 = D_801EFF7A;
        metric_2 = D_801EFF74;
        metric_3 = D_801EFF7C;
        metric_4 = D_801EFF82;
        metric_5 = D_801EFF84;
        color = 0x80;
        g_jobstts_text_color = color;
        g_jobstts_text_color_g = color;
    }
    g_jobstts_text_color_b = color;
    D_801FA7E4 = metric_0;
    D_801FA7A8 = metric_1;
    D_801FA78C = metric_2;
    D_801FA744 = metric_3;
    D_801FA7F0 = metric_4;
    D_801FA80C = metric_5;
}
