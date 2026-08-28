#include "psx/types.h"

extern void ClearOTagR(u32* ot, s32 n);

typedef struct {
    s32 log2n;
    u32* ot;
    s32 x;
    s32 y;
    u32* last;
} GsOT;

void world_gs_clearot(s32 x, s32 y, GsOT* ot) {
    ot->x = x & 0xFFFF;
    ot->y = y & 0xFFFF;
    ot->last = (u32*)((s32)ot->ot + (4 << ot->log2n) - 4);
    ClearOTagR(ot->ot, 1 << ot->log2n);
}
