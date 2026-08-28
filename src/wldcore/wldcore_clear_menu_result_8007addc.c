#include "psx/types.h"

extern s32 g_world_menu_result;

/* Clear the shared world-menu result before the next menu state runs. */
void wldcore_clear_menu_result_8007addc(void) {
    g_world_menu_result = -1;
}
