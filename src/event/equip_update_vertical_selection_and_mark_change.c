#include "psx/types.h"

extern s16 g_equip_menu_indices[];
extern s8 g_equip_queued_sound_effect_id;
extern s16 func_801C9668(s32, s32);

void equip_update_vertical_selection_and_mark_change(s32 arg0, s32 arg1, s32 arg2, s8 arg3) {
    s32 idx = arg1 & 0xFF;
    s16 v = g_equip_menu_indices[idx];
    if (v != func_801C9668(arg0 & 0xFFFF, idx)) {
        g_equip_queued_sound_effect_id = arg3;
    }
}
