#include "psx/types.h"

extern u8 g_screen_color_modulation[3];

void battle_clear_screen_color_modulation(void) {
    g_screen_color_modulation[2] = 0;
    g_screen_color_modulation[1] = 0;
    g_screen_color_modulation[0] = 0;
}
