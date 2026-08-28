#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct {
    u32* ot;      /* 0x00 */
    u8 pad[0xcc]; /* 0x04 */
    DR_MODE mode; /* 0xd0 */
} CardGfxCtx;

extern CardGfxCtx* g_card_graphics_context;

void card_set_draw_mode_and_link_ot(s32 dfe, s32 dtd, s32 tpage,
    RECT* texture_window, s32 otag_index) {
    CardGfxCtx* context = g_card_graphics_context;
    DR_MODE* mode = &context->mode;

    SetDrawMode(mode, dfe, dtd, tpage, texture_window);
    {
        CardGfxCtx* link_context = g_card_graphics_context;
        setaddr(mode, getaddr(&link_context->ot[otag_index]));
        setaddr(&link_context->ot[otag_index], mode);
    }
}
