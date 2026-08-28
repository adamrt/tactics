#include "psx/types.h"

extern s32 g_event_mode;
extern void battle_initialize_menu_primitive_colors_palette_bank_0(void);
extern void battle_initialize_menu_primitive_colors_palette_bank_1(void);

/* BUNIT.OUT 001c1650 - Select the menu-primitive palette bank based on the caller's
 * mode flag (arg1[4]) or the global event mode. */
void bunit_apply_menu_palette_for_mode(s32 unused, s32* menu_state) {
    if (menu_state[4] == 1 || g_event_mode == 1) {
        battle_initialize_menu_primitive_colors_palette_bank_1();
    } else {
        battle_initialize_menu_primitive_colors_palette_bank_0();
    }
}
