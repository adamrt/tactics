#include "psx/etc.h"
#include "psx/gpu.h"

extern int g_screen_polarity;
extern DRAWENV g_main_draw_envs[2];
extern DISPENV g_main_display_envs[2];

int main_swap_display_area(u32 otag) {
    /* Matching constraint: the retail function reserves one unused RECT. */
    volatile RECT matching_stack_space;
    int elapsed;

    g_screen_polarity = g_screen_polarity == 0;
    DrawSync(0);
    elapsed = VSync(0);

    PutDispEnv(&g_main_display_envs[g_screen_polarity]);
    PutDrawEnv(&g_main_draw_envs[g_screen_polarity]);
    DrawOTag(otag);
    FntFlush(-1);
    return elapsed;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
