#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8 g_current_ability_x;

void battle_store_ma_and_x(void) {
    s32 ma = g_current_attacker->attributes[1];
    s32 x = g_current_ability_x;

    g_current_ability_ya = x;
    g_current_ability_xa = ma;
}
