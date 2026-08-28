#include "psx/gpu.h"
#include "psx/types.h"

typedef struct JobsttsPrimSet {
    u32* ot;
} JobsttsPrimSet;

extern void func_80024E4C(DRAWENV*);

extern s16 D_801FA734;
extern s16 D_801FA790;
extern s16 D_801FA73C;
extern s16 g_jobstts_poly_ft4_count;
extern s16 D_801FA738;
extern s16 D_801FA794;
extern s16 D_801FA740;
extern s16 D_801FA79C;
extern s16 D_801FA768;
extern s16 D_801FA778;
extern s16 D_801FA784;
extern s16 D_801FA774;
extern s16 D_801FA780;
extern s16 D_801FA788;
extern s16 D_801FA7C8;
extern s16 D_801FA7EC;
extern s16 D_801FA7F4;
extern s16 D_801FA810;
extern s16 D_801FA7D8;
extern s16 D_801FA804;
extern s16 D_801FA814;
extern s16 D_801FA7CC;
extern s16 g_jobstts_draw_area_count;
extern s16 g_jobstts_drawenv_y;
extern u16 g_jobstts_otag_length;
extern JobsttsPrimSet* g_jobstts_graphics_context;
extern JobsttsPrimSet* g_jobstts_graphics_context_base;

void jobstts_swap_graphics_context_and_clear_otag(s32 first_otag) {
    DRAWENV env;
    JobsttsPrimSet* context;

    D_801FA734 = 0;
    D_801FA790 = 0;
    D_801FA73C = 0;
    g_jobstts_poly_ft4_count = 0;
    D_801FA738 = 0;
    D_801FA794 = 0;
    D_801FA740 = 0;
    D_801FA79C = 0;
    D_801FA768 = 0;
    D_801FA778 = 0;
    D_801FA784 = 0;
    D_801FA774 = 0;
    D_801FA780 = 0;
    D_801FA788 = 0;
    D_801FA7C8 = 0;
    D_801FA7EC = 0;
    D_801FA7F4 = 0;
    D_801FA810 = 0;
    D_801FA7D8 = 0;
    D_801FA804 = 0;
    D_801FA814 = 0;
    D_801FA7CC = 0;
    g_jobstts_draw_area_count = 0;
    func_80024E4C(&env);
    context = g_jobstts_graphics_context_base;
    g_jobstts_drawenv_y = env.clip.y;
    if (g_jobstts_graphics_context == context) {
        context = (JobsttsPrimSet*)((u8*)context + 0xF4);
    }
    g_jobstts_graphics_context = context;
    ClearOTag(&context->ot[first_otag], g_jobstts_otag_length - first_otag);
}
