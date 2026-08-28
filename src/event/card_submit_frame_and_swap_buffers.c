#include "psx/etc.h"
#include "psx/gpu.h"
#include "psx/types.h"

extern u8* g_card_graphics_context;
extern u8* g_card_graphics_context_base;
extern s16 g_card_poly_ft4_count;
extern u16 g_card_tile_count;
extern u16 g_card_drawenv_y;
extern u16 g_card_otag_length;
extern s8 g_card_event_speed;
extern void tick(void);

void card_submit_frame_and_swap_buffers(s32 first_otag, s32 draw_otag) {
    u32* previous_otag = *(u32**)g_card_graphics_context;
    u8* context;

    tick();
    g_card_poly_ft4_count = 0;
    g_card_tile_count = 0;
    while (DrawSync(1) != 0) {
    }
    VSync(g_card_event_speed);
    context = g_card_graphics_context_base;
    if (g_card_graphics_context == context) {
        context += 0xf4;
    }
    g_card_graphics_context = context;
    PutDispEnv((DISPENV*)(context + 0xbc));
    PutDrawEnv((DRAWENV*)(g_card_graphics_context + 0x60));
    g_card_drawenv_y = *(u16*)(g_card_graphics_context + 0x62);
    if (draw_otag != -1) {
        DrawOTag((u32)(previous_otag + draw_otag));
    }
    ClearOTag(*(u32**)g_card_graphics_context + first_otag,
        g_card_otag_length - first_otag);
}
