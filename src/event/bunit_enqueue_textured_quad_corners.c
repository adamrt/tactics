#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u16 x0;    /* 0x00 */
    u16 y0;    /* 0x02 */
    u16 x1;    /* 0x04 */
    u16 y1;    /* 0x06 */
    u16 x2;    /* 0x08 */
    u16 y2;    /* 0x0A */
    u16 x3;    /* 0x0C */
    u16 y3;    /* 0x0E */
    u16 u0;    /* 0x10 */
    u16 v0;    /* 0x12 */
    u16 u1;    /* 0x14 */
    u16 v1;    /* 0x16 */
    u16 u2;    /* 0x18 */
    u16 v2;    /* 0x1A */
    u16 u3;    /* 0x1C */
    u16 v3;    /* 0x1E */
    u16 clut;  /* 0x20 */
    u16 tpage; /* 0x22 */
} BunitSpriteDesc;

typedef struct {
    u32* ot;         /* 0x00 */
    u8 pad[0xC];     /* 0x04 */
    POLY_FT4* quads; /* 0x10 */
} BunitSpriteCtx;

extern u16 g_bunit_poly_ft4_count;
extern BunitSpriteCtx* g_bunit_graphics_context;

void bunit_enqueue_textured_quad_corners(BunitSpriteDesc* src, u8* color, s32 semi,
    s32 idx) {
    POLY_FT4* p;

    p = &g_bunit_graphics_context->quads[g_bunit_poly_ft4_count++];
    if (color != 0) {
        SetShadeTex(p, 0);
        p->r0 = color[0];
        p->g0 = color[1];
        p->b0 = color[2];
    } else {
        SetShadeTex(p, 1);
    }
    SetSemiTrans(p, semi);
    p->x0 = src->x0 + 0x80;
    p->y0 = src->y0;
    p->x1 = src->x1 + 0x80;
    p->y1 = src->y1;
    p->x2 = src->x2 + 0x80;
    p->y2 = src->y2;
    p->x3 = src->x3 + 0x80;
    p->y3 = src->y3;
    p->u0 = src->u0;
    p->v0 = src->v0;
    p->u1 = src->u1;
    p->v1 = src->v1;
    p->u2 = src->u2;
    p->v2 = src->v2;
    p->u3 = src->u3;
    p->v3 = src->v3;
    p->clut = src->clut;
    p->tpage = src->tpage;
    {
        BunitSpriteCtx* ctx = g_bunit_graphics_context;
        setaddr(p, getaddr(&ctx->ot[idx]));
        setaddr(&ctx->ot[idx], p);
    }
}
