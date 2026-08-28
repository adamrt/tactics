#include "psx/etc.h"
#include "psx/gpu.h"

extern void* g_high_overlay_load_address;
extern int g_screen_polarity;

extern void main_set_display_draw(int, int, int, u8, u8, u8);
extern void main_get_dat_as_wd(int, int, void*);
extern int main_draw_sceap(void*, u32*);

void main_build_draw_sceap(void) {
    POLY_F4 polygons[2];
    DR_MODE draw_modes[2];
    u32 otags[2][2];
    /* SetDrawMode uses this as a texture window; zero selects the full window. */
    RECT image_rect = { 0 };
    u32* current_otag;
    s16 intensity;
    int frame;

    main_set_display_draw(320, 240, 512, 0, 0, 0);
    main_get_dat_as_wd(198, 0x5000, g_high_overlay_load_address);
    frame = 0;

    SetPolyF4(&polygons[0]);
    polygons[0].r0 = 0;
    polygons[0].g0 = 0;
    polygons[0].b0 = 0;
    polygons[0].x0 = 0;
    polygons[0].y0 = 0;
    polygons[0].x1 = 320;
    polygons[0].y1 = 0;
    polygons[0].x2 = 0;
    polygons[0].y2 = 240;
    polygons[0].x3 = 320;
    polygons[0].y3 = 240;
    SetSemiTrans(&polygons[0], 1);
    polygons[1] = polygons[0];

    SetDrawMode(&draw_modes[0], 0, 0, 0x40, &image_rect);
    draw_modes[1] = draw_modes[0];

    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.w = 320;
    image_rect.h = 480;
    ClearImage(&image_rect, 0, 0, 0);
    DrawSync(0);
    SetDispMask(1);

    for (; frame < 15; frame++) {
        VSync(0);
    }

    intensity = 248;
    while (intensity >= 0) {
        current_otag = otags[g_screen_polarity];
        ClearOTag(current_otag, 2);
        g_screen_polarity[polygons].r0 = intensity;
        g_screen_polarity[polygons].g0 = intensity;
        g_screen_polarity[polygons].b0 = intensity;
        AddPrim(current_otag, &polygons[g_screen_polarity]);
        AddPrim(current_otag, &draw_modes[g_screen_polarity]);
        main_draw_sceap(current_otag, g_high_overlay_load_address);
        intensity -= 8;
    }

    for (frame = 0; frame < 180; frame++) {
        VSync(0);
    }

    intensity = 0;
    while (intensity < 256) {
        if (intensity >= 248) {
            intensity = 255;
        }

        current_otag = otags[g_screen_polarity];
        ClearOTag(current_otag, 2);
        g_screen_polarity[polygons].r0 = intensity;
        g_screen_polarity[polygons].g0 = intensity;
        g_screen_polarity[polygons].b0 = intensity;
        AddPrim(current_otag, &polygons[g_screen_polarity]);
        AddPrim(current_otag, &draw_modes[g_screen_polarity]);
        main_draw_sceap(current_otag, g_high_overlay_load_address);
        intensity += 8;
    }

    DrawSync(0);
    image_rect.x = 0;
    image_rect.y = 0;
    image_rect.w = 320;
    image_rect.h = 480;
    ClearImage(&image_rect, 0, 0, 0);
    DrawSync(0);
}
