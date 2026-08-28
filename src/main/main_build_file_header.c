#include "psx/gpu.h"

extern DRAWENV g_main_draw_envs[];
extern DISPENV g_main_display_envs[];
extern s32 g_loading_display_frame_counter;
extern void build_now_loading(u32, u32, u32);
extern void CdIntToPos(s32, void*);

s32 main_build_file_header(u32* header, s32 lba, s32 arg2, s32 arg3,
    s32 mode) {
    RECT rect;

    if (header[1] != 0) {
        return 1;
    }
    if (mode != 1) {
        g_loading_display_frame_counter = mode;
    }
    if (mode == 0) {
        SetDispMask(0);
        build_now_loading(1, 0, 0);
        rect.x = 0;
        rect.y = 0;
        rect.w = 0x100;
        rect.h = 0x1e0;
        ClearImage(&rect, 0, 0, 0);
        DrawSync(0);
        SetDefDrawEnv(&g_main_draw_envs[0], 0, 0, 0x100, 0xf0);
        SetDefDispEnv(&g_main_display_envs[0], 0, 0xf0, 0x100, 0xf0);
        SetDefDrawEnv(&g_main_draw_envs[1], 0, 0xf0, 0x100, 0xf0);
        SetDefDispEnv(&g_main_display_envs[1], 0, 0, 0x100, 0xf0);
        g_main_draw_envs[1].ofs[1] = 0xf0;
        g_main_draw_envs[1].ofs[0] = 0;
        g_main_draw_envs[0].ofs[1] = 0;
        g_main_draw_envs[0].ofs[0] = 0;
        g_main_draw_envs[1].dfe = 1;
        g_main_draw_envs[1].isbg = 1;
        g_main_draw_envs[0].dfe = 1;
        g_main_draw_envs[0].isbg = 1;
        PutDrawEnv(&g_main_draw_envs[1]);
        PutDispEnv(&g_main_display_envs[1]);
    }
    header[0] = 0;
    header[6] = 0;
    header[2] = 0;
    header[1] = 1;
    header[5] = lba;
    CdIntToPos(lba, &header[7]);
    header[4] = arg2;
    header[8] = arg3;
    return 0;
}
