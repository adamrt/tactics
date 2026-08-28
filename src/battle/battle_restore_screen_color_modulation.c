#include "psx/types.h"

extern u8 g_screen_color_modulation[3];
extern u8 g_screen_color_modulation_backup[3];

void battle_restore_screen_color_modulation(void) {
    g_screen_color_modulation[0] = g_screen_color_modulation_backup[0];
    g_screen_color_modulation[1] = g_screen_color_modulation_backup[1];
    g_screen_color_modulation[2] = g_screen_color_modulation_backup[2];
}
