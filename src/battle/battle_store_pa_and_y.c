#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8 g_current_ability_y;

void battle_store_pa_and_y(void) {
    s32 pa = g_current_attacker->attributes[0];
    s32 y = g_current_ability_y;

    g_current_ability_ya = y;
    g_current_ability_xa = pa;
}
