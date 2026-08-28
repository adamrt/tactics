#include "psx/etc.h"
#include "psx/gpu.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_frame_pacing_timer;
extern s32 g_frame_pacing;
extern s32 g_gpu_frame_counter;
extern DISPENV g_main_display_envs[];
extern DRAWENV g_main_draw_envs[];

s32 battle_frame_sync(u32 ordering_table) {
    s32 wait;
    s32 sync_wait;
    s32 timer;
    s32 sync_result;

    if (g_animation_speed == 1) {
        DrawSync(0);
        sync_wait = 0;
        goto perform_sync;
    } else {
        DrawSync(0);
        if (g_battle_game_state == 0x33 || g_battle_game_state == 0x2d) {
            timer = g_frame_pacing_timer;
            if (timer >= 0x10) {
                wait = 4;
                g_frame_pacing_timer = timer - 1;
            } else if (timer != 0) {
                wait = 3;
                g_frame_pacing_timer = timer - 1;
            } else {
                wait = 2;
            }
            sync_wait = g_frame_pacing;
            if (wait < sync_wait) {
                if (sync_wait != 1) {
                    goto perform_sync;
                }
                sync_wait = 0;
                goto perform_sync;
            }
            sync_wait = wait;
            goto perform_sync;
        } else {
            sync_wait = g_animation_speed;
        }
    }

perform_sync:
    sync_result = VSync(sync_wait);
    /* Emits nothing; forces VSync's result into $s0 before the env calls. */
    __asm__ volatile("" : "=r"(sync_result) : "0"(sync_result));
    PutDispEnv(&g_main_display_envs[g_gpu_frame_counter]);
    PutDrawEnv(&g_main_draw_envs[g_gpu_frame_counter]);
    DrawOTag(ordering_table);
    FntFlush(-1);
    return sync_result;
}
