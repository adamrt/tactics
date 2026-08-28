#include "psx/gpu.h"
#include "psx/types.h"

typedef struct P_TAG {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

typedef struct JobsttsBoardRect {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} JobsttsBoardRect;

typedef struct JobsttsTexRegion {
    u16 u;
    u16 v;
    u16 w;
    u16 h;
    u16 clut;
    u16 tpage;
} JobsttsTexRegion;

typedef struct JobsttsPrimSet {
    u32* ot;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    POLY_FT4* prims;
} JobsttsPrimSet;

extern u16 g_jobstts_poly_ft4_count;
extern JobsttsPrimSet* g_jobstts_graphics_context;

void jobstts_enqueue_textured_quad_rect(JobsttsBoardRect* rect, JobsttsTexRegion* tex,
    u8* color, s32 semitrans, s32 ot_index) {
    POLY_FT4* poly;

    poly = &g_jobstts_graphics_context->prims[g_jobstts_poly_ft4_count++];

    if (color != 0) {
        SetShadeTex(poly, 0);
        poly->r0 = color[0];
        poly->g0 = color[1];
        poly->b0 = color[2];
    } else {
        SetShadeTex(poly, 1);
    }
    SetSemiTrans(poly, semitrans);

    poly->x0 = rect->x + 0x80;
    poly->y0 = rect->y;
    poly->x1 = rect->x + (rect->w + 0x80);
    poly->y1 = rect->y;
    poly->x2 = rect->x + 0x80;
    poly->y2 = rect->y + rect->h;
    poly->x3 = rect->x + (rect->w + 0x80);
    poly->y3 = rect->y + rect->h;
    poly->u0 = tex->u;
    poly->v0 = tex->v;
    poly->u1 = tex->u + tex->w;
    poly->v1 = tex->v;
    poly->u2 = tex->u;
    poly->v2 = tex->v + tex->h;
    poly->u3 = tex->u + tex->w;
    poly->v3 = tex->v + tex->h;
    poly->clut = tex->clut;
    poly->tpage = tex->tpage;

    ((P_TAG*)poly)->addr = g_jobstts_graphics_context->ot[ot_index];
    ((P_TAG*)&g_jobstts_graphics_context->ot[ot_index])->addr = (u32)poly;
}
