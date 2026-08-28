#include "psx/gpu.h"
#include "psx/types.h"

typedef struct CardGraphicsContext {
    u32* otag;
    u8 unknown_04[0x0c];
    POLY_FT4* polygons;
    u8 unknown_14[0x28];
    u8* tiles;
    u8 unknown_40[0x20];
    DRAWENV draw_environment;
    DISPENV display_environment;
    u8 unknown_d0[0x24];
} CardGraphicsContext;

extern CardGraphicsContext* g_card_graphics_context;
extern CardGraphicsContext* g_card_graphics_context_base;
extern u16 g_card_otag_length;
extern u16 g_card_poly_ft4_capacity;
extern u16 g_card_tile_capacity;

extern void card_initialize_primitive_lists(CardGraphicsContext* context);
extern void card_submit_frame_and_swap_buffers(s32 first_otag, s32 draw_otag);

void card_initialize_graphics_contexts(
    CardGraphicsContext* contexts, u32* otags,
    s32 unused_2, s32 unused_3, s32 unused_4, POLY_FT4* polygons,
    s32 unused_6, s32 unused_7, s32 unused_8, s32 unused_9,
    s32 unused_10, s32 unused_11, s32 unused_12, s32 unused_13,
    s32 unused_14, s32 unused_15, u8* tiles) {
    s32 i;
    s32 display_height;
    s32 y_offset;
    s32 context_offset;
    CardGraphicsContext* setup_context;

    i = 0;
    display_height = 0xf0;
    y_offset = 0;
    context_offset = 0;
    g_card_graphics_context_base = contexts;
    g_card_graphics_context = contexts;
    for (; i < 2; i++) {
        setup_context = (CardGraphicsContext*)((u8*)g_card_graphics_context_base + context_offset);
        setup_context->otag = otags + g_card_otag_length * i;
        setup_context->polygons = polygons + g_card_poly_ft4_capacity * i;
        setup_context->tiles = tiles + g_card_tile_capacity * i * 0x10;
        card_initialize_primitive_lists(setup_context);
        SetDefDrawEnv(&((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment,
            0, y_offset, 0x100, display_height);
        SetDefDispEnv(&((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->display_environment,
            0,
            i == 0 ? 0xf0 : 0, 0x100,
            display_height);
        ((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment.isbg = 0;
        ((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment.r0 = 0;
        ((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment.g0 = 0;
        ((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment.b0 = 0;
        ((CardGraphicsContext*)(context_offset + (s32)g_card_graphics_context_base))->draw_environment.ofs[0] = -0x80;
        y_offset += 0xf0;
        context_offset += 0xf4;
    }
    card_submit_frame_and_swap_buffers(0, -1);
    card_submit_frame_and_swap_buffers(0, -1);
}
