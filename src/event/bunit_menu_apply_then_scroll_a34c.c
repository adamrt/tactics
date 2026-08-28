#include "psx/types.h"

extern void bunit_init_scrollable_list_menu_core(s32 a0, s32 a1, s32 a2);
extern void bunit_draw_scrollable_list_menu(s32 a0);

void bunit_menu_apply_then_scroll_a34c(s32 a0, s32 a1, s32 a2, s32 a3) {
    bunit_init_scrollable_list_menu_core(a0, a1, a2);
    bunit_draw_scrollable_list_menu(a3);
}
