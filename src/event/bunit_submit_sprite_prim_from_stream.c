#include "psx/types.h"

extern u32 func_8002398C(s32 a0, u8 a1, s32 a2, s32 a3);
extern void bunit_enqueue_draw_mode(s32 a0, s32 a1, u32 a2, s32 a3, s32 a4);
extern s16 g_bunit_otag_index;

/* BUNIT.OUT 001c9634 - Build a TPage id from data[2] and submit a sprite prim
 * to the current OT. Returns the next command pointer. */
u8* bunit_submit_sprite_prim_from_stream(u8* data) {
    bunit_enqueue_draw_mode(0, 0, func_8002398C(0, data[2], 0x100, 0) & 0xFFFF, 0, g_bunit_otag_index);
    return data + data[1];
}
