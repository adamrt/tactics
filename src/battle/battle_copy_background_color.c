#include "psx/types.h"

extern u8 g_battle_background_color[];
extern u8 g_battle_background_color_backup[];

void battle_copy_background_color(void) {
    g_battle_background_color_backup[0] = g_battle_background_color[0];
    g_battle_background_color_backup[1] = g_battle_background_color[1];
    g_battle_background_color_backup[2] = g_battle_background_color[2];
}
