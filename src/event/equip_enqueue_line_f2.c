#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

/* LINE_F2 primitive (the pool at graphics context +0x24 is initialised with
   SetLineF2). */
typedef struct EquipLineF2 {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} EquipLineF2;

typedef struct {
    u32* ot;            /* 0x00 */
    u8 pad[0x20];       /* 0x04 */
    EquipLineF2* lines; /* 0x24 */
} EquipGfxCtx;

extern u16 g_equip_line_f2_count;
extern EquipGfxCtx* g_equip_graphics_context;

/* `rect` carries the two endpoints as (x0, y0, x1, y1). */
void equip_enqueue_line_f2(const RECT* rect, const u8* color,
    s32 semitrans, s32 otag_index) {
    EquipLineF2* line;
    const RECT* endpoints = rect;
    u16 index = g_equip_line_f2_count;

    g_equip_line_f2_count = index + 1;
    line = &g_equip_graphics_context->lines[index];
    line->r = color[0];
    line->g = color[1];
    line->b = color[2];
    SetSemiTrans(line, semitrans & 0xff);
    line->x0 = endpoints->x + 0x80;
    line->y0 = endpoints->y;
    line->x1 = endpoints->w + 0x80;
    line->y1 = endpoints->h;
    {
        EquipGfxCtx* context = g_equip_graphics_context;
        setaddr(line, getaddr(&context->ot[otag_index]));
        setaddr(&context->ot[otag_index], line);
    }
}
