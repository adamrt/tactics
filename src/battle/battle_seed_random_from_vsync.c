#include "psx/types.h"

extern s32 VSync(s32 mode);
extern s32 g_battle_rand16_state;

void battle_seed_random_from_vsync(void) {
    g_battle_rand16_state = VSync(-1);
}
