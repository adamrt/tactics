#include "psx/gpu.h"

extern int g_screen_polarity;
extern u32 g_squaresoft_logo_image_words[];

extern int main_draw_squaresoft_logo(void*, u32*);

void main_squaresoft_fade_out(void) {
    POLY_F4 polygons[2];
    DR_MODE draw_modes[2];
    u32 otags[2][2];
    /* SetDrawMode uses this as a texture window; zero selects the full window. */
    RECT image_rect = { 0 };
    u32* otag_base;
    s16 intensity;
    int buffer;

    intensity = 0;
    SetPolyF4(&polygons[0]);
    polygons[0].r0 = 0;
    polygons[0].g0 = 0;
    polygons[0].b0 = 0;
    polygons[0].x0 = 0;
    polygons[0].y0 = 0;
    polygons[0].x1 = 320;
    polygons[0].y1 = 0;
    polygons[0].x2 = 0;
    polygons[0].y2 = 256;
    polygons[0].x3 = 320;
    polygons[0].y3 = 256;
    SetSemiTrans(&polygons[0], 1);
    polygons[1] = polygons[0];

    SetDrawMode(&draw_modes[0], 0, 0, 0x40, &image_rect);
    draw_modes[1] = draw_modes[0];
    otag_base = otags[0];

    while (intensity < 256) {
        if (intensity >= 248) {
            intensity = 255;
        }

        buffer = g_screen_polarity;
        ClearOTag(otag_base + buffer * 2, 2);
        g_screen_polarity[polygons].r0 = intensity;
        g_screen_polarity[polygons].g0 = intensity;
        g_screen_polarity[polygons].b0 = intensity;
        AddPrim(otag_base + buffer * 2, &polygons[g_screen_polarity]);
        AddPrim(otag_base + buffer * 2, &draw_modes[g_screen_polarity]);
        main_draw_squaresoft_logo(otag_base + buffer * 2, g_squaresoft_logo_image_words);
        intensity += 8;
    }

    DrawSync(0);
    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.w = 256;
    image_rect.h = 480;
    ClearImage(&image_rect, 0, 0, 0);
    DrawSync(0);
}
