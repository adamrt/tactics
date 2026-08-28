#include "psx/gpu.h"
#include "psx/types.h"

void attack_set_formation_icon_uv(POLY_FT4* poly, s32 index) {
    register s32 u __asm__("$6");
    register s32 v __asm__("$3");
    register s32 v_start __asm__("$2");
    register s32 u_end __asm__("$7");

    u = index % 7;
    u *= 0x20;
    v = (index / 7) * 0x30;
    v_start = v + 0x28;
    __asm__("" : "=r"(u) : "0"(u));
    u_end = u + 0x1f;
    v += 0x58;
    poly->u0 = u;
    poly->u2 = u;
    poly->u1 = u_end;
    poly->u3 = u_end;
    poly->v0 = v_start;
    poly->v1 = v_start;
    poly->v2 = v;
    poly->v3 = v;
    poly->tpage = GetTPage(0, 0, 0x100, 0);
    poly->clut = GetClut(((index % 3) << 4) + 0x100, index / 3);
}
