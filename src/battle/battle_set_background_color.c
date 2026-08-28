#include "psx/types.h"

extern u8 g_battle_background_color[];
extern void func_800e77b8(s32 mode, s32 red, s32 green, s32 blue);

void battle_set_background_color(s32 red, s32 green, s32 blue) {
    g_battle_background_color[0] = red;
    g_battle_background_color[1] = green;
    g_battle_background_color[2] = blue;
    func_800e77b8(9, g_battle_background_color[0],
        g_battle_background_color[1],
        g_battle_background_color[2]);
}
