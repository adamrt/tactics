#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8 g_current_ability_y;

void battle_store_pa_and_pa_plus_y_divided_by_two(void) {
    g_current_ability_xa = g_current_attacker->attributes[0];
    g_current_ability_ya = (g_current_attacker->attributes[0] + g_current_ability_y) >> 1;
}
