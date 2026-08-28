#include "psx/types.h"

extern s8 g_bunit_otag_index_locked;
extern s16 g_bunit_otag_index;
extern u16 g_bunit_draw_area_y;
extern void bunit_enqueue_draw_area(u16* area, s32 otag_index);

/* BUNIT.OUT 001cb20c - When the OT index is not locked, reset the shared draw
 * area's y to 0 and enqueue it at the next OT slot. Twin of
 * jobstts_parse_add_next_otag_draw_area. */
u8* bunit_parse_add_next_otag_draw_area(u8* data) {
    if (g_bunit_otag_index_locked == 0) {
        s32 otag_index = g_bunit_otag_index;
        u16* area = &g_bunit_draw_area_y;
        *area = 0;
        area--;
        bunit_enqueue_draw_area(area, otag_index + 1);
    }
    return data + data[1];
}
