#include "psx/gpu.h"
#include "psx/gte.h"

extern const RECT g_deployment_clear_rect;
extern s32 g_gpu_frame_counter;
extern s32 g_font_print_enabled;
extern DRAWENV g_main_draw_envs[];
extern DISPENV g_main_display_envs[];
extern void main_get_efc_fnt(void);

void battle_initialize_deployment_display(
    s32 width, s32 height, s32 projection,
    u8 red, u8 green, u8 blue) {
    RECT clear_rect;
    s32 second_y;

    clear_rect = g_deployment_clear_rect;
    second_y = -(height != 0x1e0) & 0xf0;

    SetDispMask(0);
    ResetGraph(1);
    SetGeomOffset(width / 2, height / 2);
    SetGeomScreen(projection);

    SetDefDrawEnv(&g_main_draw_envs[0], -0x80, 0,
        width + 0x80, height);
    SetDefDispEnv(&g_main_display_envs[0], 0, second_y,
        width, height);
    SetDefDrawEnv(&g_main_draw_envs[1], -0x80, second_y,
        width + 0x80, height);
    SetDefDispEnv(&g_main_display_envs[1], 0, 0,
        width, height);

    g_main_draw_envs[0].dtd = g_main_draw_envs[1].dtd = 1;
    g_main_draw_envs[0].isbg = g_main_draw_envs[1].isbg = 0;
    g_main_draw_envs[0].r0 = red;
    g_main_draw_envs[0].g0 = green;
    g_main_draw_envs[0].b0 = blue;
    g_main_draw_envs[1].r0 = red;
    g_main_draw_envs[1].g0 = green;
    g_main_draw_envs[1].b0 = blue;

    ClearImage(&clear_rect, 0, 0, 0);
    DrawSync(0);
    if (g_font_print_enabled != 0) {
        main_get_efc_fnt();
    }
    PutDispEnv(&g_main_display_envs[g_gpu_frame_counter]);
    PutDrawEnv(&g_main_draw_envs[g_gpu_frame_counter]);
}
