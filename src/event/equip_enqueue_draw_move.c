#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct EquipMove {
    u32 tag;
    u32 code0;
    u32 code1;
    s16 x;
    s16 y;
    s16 u;
    s16 v;
    s16 w;
    s16 h;
} EquipMove;

typedef struct {
    u32* ot;          /* 0x00 */
    u8 pad[0x54];     /* 0x04 */
    EquipMove* moves; /* 0x58 */
} EquipGfxCtx;

extern u16 g_equip_draw_move_count;
extern EquipGfxCtx* g_equip_graphics_context;
extern void equip_set_draw_move(EquipMove* prim);

void equip_enqueue_draw_move(const RECT* rect, s32 u, s32 v,
    s32 otag_index) {
    EquipMove* prim;
    const RECT* src = rect;
    u16 index = g_equip_draw_move_count;

    g_equip_draw_move_count = index + 1;
    prim = &g_equip_graphics_context->moves[index];
    equip_set_draw_move(prim);
    prim->x = src->x;
    prim->y = src->y;
    prim->u = u;
    prim->v = v;
    prim->w = src->w;
    prim->h = src->h;
    {
        EquipGfxCtx* context = g_equip_graphics_context;
        setaddr(prim, getaddr(&context->ot[otag_index]));
        setaddr(&context->ot[otag_index], prim);
    }
}
