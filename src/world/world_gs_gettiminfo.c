#include "psx/types.h"

typedef struct {
    u32 pmode;
    s16 px;
    s16 py;
    s16 pw;
    s16 ph;
    u32* pixel;
    s16 cx;
    s16 cy;
    s16 cw;
    s16 ch;
    u32* clut;
} WorldTimInfo;

void world_gs_gettiminfo(u32* tim, WorldTimInfo* im) {
    u32* p;

    im->pmode = *tim;
    if ((im->pmode >> 3) & 1) {
        tim++;
        p = tim + (*tim >> 2);
        tim++;
        im->cx = ((u16*)tim)[0];
        im->cy = ((u16*)tim)[1];
        tim++;
        im->cw = ((u16*)tim)[0];
        im->ch = ((u16*)tim)[1];
        tim++;
        im->clut = tim;
        p++;
        im->px = ((u16*)p)[0];
        im->py = ((u16*)p)[1];
        p++;
        im->pw = ((u16*)p)[0];
        im->ph = ((u16*)p)[1];
        p++;
        im->pixel = p;
    } else {
        tim += 2;
        im->px = ((u16*)tim)[0];
        im->py = ((u16*)tim)[1];
        tim++;
        im->pw = ((u16*)tim)[0];
        im->ph = ((u16*)tim)[1];
        tim++;
        im->pixel = tim;
    }
}
