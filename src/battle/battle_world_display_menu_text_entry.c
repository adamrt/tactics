#include "psx/types.h"

extern void call_inner_subroutine(s32, s32, s32, s32);
extern u32 D_8014B394;

void battle_world_display_menu_text_entry(s32 a0, s32 a1, s32 a2) {
    *(u32**)0x80173CA8 = &D_8014B394;
    call_inner_subroutine(a0, a1, a2, 0);
}
