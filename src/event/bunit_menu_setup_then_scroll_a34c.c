#include "psx/types.h"

extern void bunit_init_scrollable_list_menu(s32 a0, s32 a1, s32 a2, s32 a3);
extern void bunit_draw_scrollable_list_menu(s32 a0);

void bunit_menu_setup_then_scroll_a34c(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    bunit_init_scrollable_list_menu(a0, a1, a2, a3);
    bunit_draw_scrollable_list_menu(a4);
}
