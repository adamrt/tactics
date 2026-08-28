#include "psx/types.h"

extern s16 g_battle_gfx_counter;

s16 battle_increment_gfx_counter(void) {
    g_battle_gfx_counter = (g_battle_gfx_counter + 1) % 0x100;
    return g_battle_gfx_counter;
}
