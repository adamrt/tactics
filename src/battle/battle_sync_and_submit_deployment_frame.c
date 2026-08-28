#include "psx/etc.h"
#include "psx/gpu.h"

extern s32 g_gpu_frame_counter;
extern DISPENV g_main_display_envs[];
extern DRAWENV g_main_draw_envs[];

s32 battle_sync_and_submit_deployment_frame(u32 ordering_table) {
    s32 sync_result;

    DrawSync(0);
    sync_result = VSync(0);
    PutDispEnv(&g_main_display_envs[g_gpu_frame_counter]);
    PutDrawEnv(&g_main_draw_envs[g_gpu_frame_counter]);
    DrawOTag(ordering_table);
    FntFlush(-1);
    return sync_result;
}
