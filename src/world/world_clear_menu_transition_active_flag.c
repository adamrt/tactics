#include "psx/types.h"

extern u16 g_world_menu_transition_active;

void world_clear_menu_transition_active_flag(void) {
    g_world_menu_transition_active = 0;
}
