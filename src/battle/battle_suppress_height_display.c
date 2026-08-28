#include "psx/types.h"

extern s16 g_battle_height_display_suppressed;

void battle_suppress_height_display(void) {
    g_battle_height_display_suppressed = 1;
}
