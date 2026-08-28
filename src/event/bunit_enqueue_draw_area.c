#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u32 tag;
    u32 code[2];
} DR_AREA;

typedef struct {
    u32* ot;       /* 0x00 */
    u8 pad[0x58];  /* 0x04 */
    DR_AREA* area; /* 0x5C */
} BunitDb;

extern u16 D_801ECA90;
extern u16 D_801ECAB0;
extern BunitDb* g_bunit_graphics_context;

extern DR_AREA* SetDrawArea(DR_AREA*, RECT*);

void bunit_enqueue_draw_area(RECT* rect, s32 idx) {
    DR_AREA* p;

    if (D_801ECA90 < 0x64) {
        rect->y += 0xF0;
    }

    p = &g_bunit_graphics_context->area[D_801ECAB0++];
    SetDrawArea(p, rect);
    {
        BunitDb* db = g_bunit_graphics_context;
        setaddr(p, getaddr(&db->ot[idx]));
        setaddr(&db->ot[idx], p);
    }
}
