#include "psx/types.h"

extern void (*g_world_inner_subroutine_callback)(void);
extern void world_display_menu_text(void);
extern void world_call_inner_subroutine_on_main_thread(s32 p1, s32 p2, s32 p3,
    s32 p4);

void battle_world_display_specific_menu_text(s32 p1, s32 p2, s32 display_text) {
    g_world_inner_subroutine_callback = world_display_menu_text;
    world_call_inner_subroutine_on_main_thread(0, p1, p2, display_text);
}
