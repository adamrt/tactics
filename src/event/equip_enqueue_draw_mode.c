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
} EquipGfxCtx;

extern u16 g_equip_draw_mode_count;
extern EquipGfxCtx* g_equip_graphics_context;

void equip_enqueue_draw_mode(s32 dfe, s32 dtd, s32 tpage, RECT* tw, s32 idx) {
    DR_MODE* p;

    p = &g_equip_graphics_context->mode[g_equip_draw_mode_count++];
    SetDrawMode(p, dfe, dtd, tpage, tw);
    {
        EquipGfxCtx* context = g_equip_graphics_context;
        setaddr(p, getaddr(&context->ot[idx]));
        setaddr(&context->ot[idx], p);
    }
}
