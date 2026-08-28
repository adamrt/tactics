#include "psx/types.h"

extern u32 g_battle_graphics_state_words[4];

void battle_clear_four_graphics_state_words(void) {
    g_battle_graphics_state_words[0] = 0;
    g_battle_graphics_state_words[1] = 0;
    g_battle_graphics_state_words[2] = 0;
    g_battle_graphics_state_words[3] = 0;
}
