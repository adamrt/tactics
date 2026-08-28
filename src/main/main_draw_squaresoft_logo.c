#include "psx/etc.h"
#include "psx/gpu.h"

extern int g_screen_polarity;
extern DRAWENV g_main_draw_envs[2];
extern DISPENV g_main_display_envs[2];

int main_draw_squaresoft_logo(u32 otag, u32* image) {
    RECT destination;
    int elapsed;

    g_screen_polarity = g_screen_polarity == 0;
    DrawSync(0);
    elapsed = VSync(0);

    PutDispEnv(&g_main_display_envs[g_screen_polarity]);
    PutDrawEnv(&g_main_draw_envs[g_screen_polarity]);

    destination.x = 70;
    destination.y = g_main_draw_envs[g_screen_polarity].clip.y + 112;
    destination.w = 180;
    destination.h = 16;
    LoadImage(&destination, image);

    DrawOTag(otag);
    FntFlush(-1);
    return elapsed;
}
