#include "psx/types.h"

extern s32 g_battle_status_menu_requested;
extern s32 g_battle_status_menu_unknown;

void battle_clear_status_menu_state(void) {
    g_battle_status_menu_requested = 0;
    g_battle_status_menu_unknown = 0;
}
