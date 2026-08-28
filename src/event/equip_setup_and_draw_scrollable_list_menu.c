#include "psx/types.h"

extern void equip_init_scrollable_list_menu_core(s32 a0, s32 a1, s32 a2);
extern void equip_draw_scrollable_list_menu(s32 a0);

void equip_setup_and_draw_scrollable_list_menu(s32 a0, s32 a1, s32 a2, s32 a3) {
    equip_init_scrollable_list_menu_core(a0, a1, a2);
    equip_draw_scrollable_list_menu(a3);
}
