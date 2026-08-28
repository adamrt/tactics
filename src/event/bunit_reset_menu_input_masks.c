#include "psx/types.h"

extern u16 g_bunit_menu_input_mask;
extern u32 g_bunit_menu_input_repeat_mask;
extern u32 g_bunit_menu_input_active_mask;

/* Reset the three masks consumed by the BUNIT menu-input processor. */
void bunit_reset_menu_input_masks(void) {
    g_bunit_menu_input_mask = 0;
    g_bunit_menu_input_repeat_mask = 0;
    g_bunit_menu_input_active_mask = 0;
}
