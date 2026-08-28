#include "psx/types.h"

extern u8 g_battle_background_color[];
extern u8 g_battle_background_color_backup[];
extern void func_800e77b8(s32 mode, s32 red, s32 green, s32 blue);

void battle_restore_background_color(void) {
    g_battle_background_color[0] = g_battle_background_color_backup[0];
    g_battle_background_color[1] = g_battle_background_color_backup[1];
    g_battle_background_color[2] = g_battle_background_color_backup[2];
    func_800e77b8(9, g_battle_background_color[0],
        g_battle_background_color[1],
        g_battle_background_color[2]);
}
