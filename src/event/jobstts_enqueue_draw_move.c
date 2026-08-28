#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

/* libgpu DR_MOVE packet. */
typedef struct JobsttsMove {
    u32 tag;
    u32 code0;
    u32 code1;
    s16 x;
    s16 y;
    s16 u;
    s16 v;
    s16 w;
    s16 h;
} JobsttsMove;

typedef struct {
    u32* ot;            /* 0x00 */
    u8 pad[0x54];       /* 0x04 */
    JobsttsMove* moves; /* 0x58 */
} JobsttsGfxCtx;

extern u16 g_jobstts_draw_move_count;
extern JobsttsGfxCtx* g_jobstts_graphics_context;

void jobstts_enqueue_draw_move(const RECT* rect, s32 u, s32 v, s32 otag_index) {
    JobsttsMove* prim;
    const RECT* src = rect;
    u16 index = g_jobstts_draw_move_count;

    g_jobstts_draw_move_count = index + 1;
    prim = &g_jobstts_graphics_context->moves[index];
    SetDrawMove(prim);
    prim->x = src->x;
    prim->y = src->y;
    prim->u = u;
    prim->v = v;
    prim->w = src->w;
    prim->h = src->h;
    {
        JobsttsGfxCtx* context = g_jobstts_graphics_context;
        setaddr(prim, getaddr(&context->ot[otag_index]));
        setaddr(&context->ot[otag_index], prim);
    }
}
