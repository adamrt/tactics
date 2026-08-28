#include "psx/gpu.h"
#include "psx/types.h"

void battle_make_default_poly_ft4(POLY_FT4* p) {
    SetPolyFT4(p);
    SetShadeTex(p, 0);
    p->r0 = 0x80;
    p->g0 = 0x80;
    p->b0 = 0x80;
    p->u1 = 1;
    p->v2 = 1;
    p->u3 = 1;
    p->v3 = 1;
    p->u0 = 0;
    p->v0 = 0;
    p->v1 = 0;
    p->u2 = 0;
    p->x0 = -0x200;
    p->y0 = 0;
    p->x1 = -0x200;
    p->y1 = 0;
    p->x2 = -0x200;
    p->y2 = 0;
    p->x3 = -0x200;
    p->y3 = 0;
    p->tpage = GetTPage(0, 0, 0x1C0, 0);
    p->clut = 0x7C3C;
}
