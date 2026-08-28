#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u8 u0;
    u8 pad0;
    u8 v0;
    u8 pad1;
    s16 w;
    s16 h;
    s16 dx;
    s16 dy;
} AttackSpriteRect;

typedef struct {
    s16 x;
    s16 y;
} AttackPoint;

typedef struct {
    s16 tpage;
    u16 clut;
} AttackTexInfo;

void attack_configure_scaled_poly_ft4(POLY_FT4* poly, AttackTexInfo* tex, AttackPoint* origin, AttackSpriteRect* rect, AttackPoint* scale, POLY_FT4* base) {
    s16 scale_x;
    s16 scale_y;
    s32 dx;
    s32 dy;
    s32 w;
    s32 h;

    scale_x = scale->x;
    dx = (rect->dx * scale_x) / 4096;
    scale_y = scale->y;
    dy = (rect->dy * scale_y) / 4096;
    w = (rect->w * scale_x) / 4096;
    h = (rect->h * scale_y) / 4096;
    if (w < 0) {
        w = -w;
    }
    if (h < 0) {
        h = -h;
    }

    poly->tpage = GetTPage(0, 0, tex->tpage, tex->clut & 0xF00);
    poly->u0 = rect->u0;
    poly->v0 = rect->v0;
    poly->u1 = rect->u0 + rect->w;
    poly->v1 = rect->v0;
    poly->u2 = rect->u0;
    poly->v2 = rect->v0 + rect->h;
    poly->u3 = rect->u0 + rect->w;
    poly->v3 = rect->v0 + rect->h;
    poly->x0 = origin->x + dx + base->x0;
    poly->y0 = origin->y + dy + base->y0;
    poly->x1 = origin->x + dx + base->x0 + w;
    poly->y1 = origin->y + dy + base->y0;
    poly->x2 = origin->x + dx + base->x0;
    poly->y2 = origin->y + dy + base->y0 + h;
    poly->x3 = origin->x + dx + base->x0 + w;
    poly->y3 = origin->y + dy + base->y0 + h;
}
