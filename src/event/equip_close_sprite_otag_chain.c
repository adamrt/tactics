#include "psx/types.h"

extern s8 g_equip_zoom_draw_area_active;
extern s16 g_equip_sprite_ot_index;
extern u16 D_801D876A;
extern void func_801CA648(u16* addr, s32 val);

/* EQUIP.OUT 001cd4a4 - Terminate the current sprite OT chain when disabled flag
 * g_equip_zoom_draw_area_active is clear: write a zero terminator and link the head pointer. */
u8* equip_close_sprite_otag_chain(u8* stream) {
    if (g_equip_zoom_draw_area_active == 0) {
        s32 otag_index = g_equip_sprite_ot_index;
        u16* ot_terminator = &D_801D876A;
        *ot_terminator = 0;
        ot_terminator--;
        func_801CA648(ot_terminator, otag_index + 1);
    }
    return stream + stream[1];
}
