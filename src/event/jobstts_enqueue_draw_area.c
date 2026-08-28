#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u32 tag;
    u32 code[2];
} DR_AREA;

typedef struct {
    u32* ot;       /* 0x00 */
    u8 pad[0x58];  /* 0x04 */
    DR_AREA* area; /* 0x5C */
} JobsttsGfxCtx;

extern u16 g_jobstts_drawenv_y;
extern u16 g_jobstts_draw_area_count;
extern JobsttsGfxCtx* g_jobstts_graphics_context;

extern DR_AREA* SetDrawArea(DR_AREA*, RECT*);

/* Queue a drawing-area primitive, shifting it to the back buffer when needed. */
void jobstts_enqueue_draw_area(RECT* rect, s32 idx) {
    DR_AREA* p;

    if (g_jobstts_drawenv_y < 0x64) {
        rect->y += 0xF0;
    }

    p = &g_jobstts_graphics_context->area[g_jobstts_draw_area_count++];
    SetDrawArea(p, rect);
    {
        JobsttsGfxCtx* context = g_jobstts_graphics_context;
        setaddr(p, getaddr(&context->ot[idx]));
        setaddr(&context->ot[idx], p);
    }
}
