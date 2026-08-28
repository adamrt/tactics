#include "psx/types.h"

extern void bunit_enqueue_draw_area(s16*, s32);
extern s8 g_bunit_otag_index_locked;
extern s16 g_bunit_otag_index;
extern s16 g_bunit_draw_area[];

/* Twin of jobstts_parse_release_otag_lock_and_add_draw_area (BUNIT does not
 * advance the OT index here). */
u8* bunit_parse_release_otag_lock_and_add_draw_area(u8* data) {
    if (g_bunit_otag_index_locked != 0) {
        g_bunit_draw_area[1] = 0;
        bunit_enqueue_draw_area(&g_bunit_draw_area[0], g_bunit_otag_index + 1);
        g_bunit_otag_index_locked = 0;
    }
    return data + data[1];
}
