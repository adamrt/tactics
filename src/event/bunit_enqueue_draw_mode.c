#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u32* ot;       /* 0x00 */
    u8 pad[0x5C];  /* 0x04 */
    DR_MODE* mode; /* 0x60 */
} BunitDb;

extern u16 D_801ECABC;
extern BunitDb* g_bunit_graphics_context;

void bunit_enqueue_draw_mode(s32 dfe, s32 dtd, s32 tpage, RECT* tw,
    s32 idx) {
    DR_MODE* p;

    p = &g_bunit_graphics_context->mode[D_801ECABC++];
    SetDrawMode(p, dfe, dtd, tpage, tw);
    {
        BunitDb* db = g_bunit_graphics_context;
        setaddr(p, getaddr(&db->ot[idx]));
        setaddr(&db->ot[idx], p);
    }
}
