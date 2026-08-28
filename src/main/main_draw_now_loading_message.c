#include "psx/gpu.h"

extern s32 g_loading_display_frame_counter;
extern DRAWENV g_main_draw_envs[2];
extern DISPENV g_main_display_envs[2];
extern u32 g_now_loading_otags[2][2];

extern void main_add_now_loading_to_otag(u32 otag);

void main_draw_now_loading_message(void) {
    s32 frame;
    u32* otag;

    frame = g_loading_display_frame_counter;
    if (frame != -1) {
        frame++;
        g_loading_display_frame_counter = frame;
        if (frame >= 0x40) {
            frame &= 1;
            PutDrawEnv(&g_main_draw_envs[frame]);
            PutDispEnv(&g_main_display_envs[frame]);
            otag = g_now_loading_otags[frame];
            ClearOTag(otag, 2);
            main_add_now_loading_to_otag((u32)otag);
            DrawOTag((u32)otag);
            SetDispMask(1);
            g_loading_display_frame_counter &= 0x41;
        }
    }
}
