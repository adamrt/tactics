#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u32 tag; /* 0x00 */
    u8 r0;   /* 0x04 */
    u8 g0;   /* 0x05 */
    u8 b0;   /* 0x06 */
    u8 code; /* 0x07 */
    s16 x0;  /* 0x08 */
    s16 y0;  /* 0x0A */
    u8 r1;   /* 0x0C */
    u8 g1;   /* 0x0D */
    u8 b1;   /* 0x0E */
    u8 pad1; /* 0x0F */
    s16 x1;  /* 0x10 */
    s16 y1;  /* 0x12 */
    u8 r2;   /* 0x14 */
    u8 g2;   /* 0x15 */
    u8 b2;   /* 0x16 */
    u8 pad2; /* 0x17 */
    s16 x2;  /* 0x18 */
    s16 y2;  /* 0x1A */
    u8 r3;   /* 0x1C */
    u8 g3;   /* 0x1D */
    u8 b3;   /* 0x1E */
    u8 pad3; /* 0x1F */
    s16 x3;  /* 0x20 */
    s16 y3;  /* 0x22 */
} BunitPolyG4;

typedef struct {
    u32* ot;            /* 0x00 */
    u8 pad[0x18];       /* 0x04 */
    BunitPolyG4* quads; /* 0x1C */
} BunitQuadCtx;

extern u16 D_801ECA2C;
extern BunitQuadCtx* g_bunit_graphics_context;

void bunit_enqueue_gouraud_quad(u16* pts, u8* color, s32 semi, s32 idx) {
    BunitPolyG4* p;

    p = &g_bunit_graphics_context->quads[D_801ECA2C++];
    SetSemiTrans(p, semi);
    p->x0 = pts[0] + 0x80;
    p->y0 = pts[1];
    p->x1 = pts[2] + 0x80;
    p->y1 = pts[3];
    p->x2 = pts[4] + 0x80;
    p->y2 = pts[5];
    p->x3 = pts[6] + 0x80;
    p->y3 = pts[7];
    p->r0 = color[0];
    p->g0 = color[1];
    p->b0 = color[2];
    p->r1 = color[3];
    p->g1 = color[4];
    p->b1 = color[5];
    p->r2 = color[6];
    p->g2 = color[7];
    p->b2 = color[8];
    p->r3 = color[9];
    p->g3 = color[10];
    p->b3 = color[11];
    {
        BunitQuadCtx* ctx = g_bunit_graphics_context;
        setaddr(p, getaddr(&ctx->ot[idx]));
        setaddr(&ctx->ot[idx], p);
    }
}
