#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8 g_current_ability_weapon_power;

void battle_store_pa_and_weapon_power(void) {
    s32 pa = g_current_attacker->attributes[0];
    s32 weapon_power = g_current_ability_weapon_power;

    g_current_ability_ya = weapon_power;
    g_current_ability_xa = pa;
}
