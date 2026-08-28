#include "psx/types.h"

extern s32 g_status_screen_selected;

void battle_enter_status_screen_selection(void) {
    if (g_status_screen_selected != 0) {
        g_status_screen_selected++;
    } else {
        g_status_screen_selected = 1;
    }
}
