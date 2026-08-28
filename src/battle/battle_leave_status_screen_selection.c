#include "psx/types.h"

extern s32 g_status_screen_selected;

void battle_leave_status_screen_selection(void) {
    g_status_screen_selected = 0;
}
