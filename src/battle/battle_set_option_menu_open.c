#include "psx/types.h"

extern u16 g_option_menu_open;

/* Sets the "an options/menu overlay is on screen" flag; the matching clear is
 * battle_clear_option_menu_open. */
void battle_set_option_menu_open(void) {
    g_option_menu_open = 1;
}
