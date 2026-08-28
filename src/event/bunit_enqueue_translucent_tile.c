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
    u8 r;    /* 0x04 */
    u8 g;    /* 0x05 */
    u8 b;    /* 0x06 */
    u8 code; /* 0x07 */
    s16 x0;  /* 0x08 */
    s16 y0;  /* 0x0A */
    s16 w;   /* 0x0C */
    s16 h;   /* 0x0E */
} BunitTile;

typedef struct {
    u16 x; /* 0x00 */
    u16 y; /* 0x02 */
    u16 w; /* 0x04 */
    u16 h; /* 0x06 */
} BunitRect;

typedef struct {
    u32* ot;          /* 0x00 */
    u8 pad[0x38];     /* 0x04 */
    BunitTile* tiles; /* 0x3C */
} BunitGfxCtx;

extern u16 D_801ECAC4;
extern BunitGfxCtx* g_bunit_graphics_context;

void bunit_enqueue_translucent_tile(BunitRect* rect, u8* color, u8 semi, s32 idx) {
    BunitTile* p;

    p = &g_bunit_graphics_context->tiles[D_801ECAC4++];
    p->r = color[0];
    p->g = color[1];
    p->b = color[2];
    SetSemiTrans(p, semi);
    p->x0 = rect->x + 0x80;
    p->y0 = rect->y;
    p->w = rect->w;
    p->h = rect->h;
    {
        BunitGfxCtx* ctx = g_bunit_graphics_context;
        setaddr(p, getaddr(&ctx->ot[idx]));
        setaddr(&ctx->ot[idx], p);
    }
}
