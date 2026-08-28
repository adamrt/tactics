#include "psx/types.h"

extern void call_inner_subroutine(s32 a, s32 b, s32 c, s32 d);
extern u8* g_call_inner_subroutine_target;
extern u8 D_8014B394;

void battle_world_display_specific_menu_text(s32 arg0, s32 arg1, s32 arg2) {
    g_call_inner_subroutine_target = &D_8014B394;
    call_inner_subroutine(0, arg0, arg1, arg2);
}
