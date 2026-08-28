#include "fft/battle.h"

extern battle_stats_t* g_current_attacker;
extern s16 g_current_ability_xa;
extern u8 g_current_ability_weapon_element;

void battle_apply_weapon_element_strengthen(void) {
    if (g_current_attacker->elemental_affinity[4] & g_current_ability_weapon_element) {
        g_current_ability_xa = g_current_ability_xa * 5 / 4;
    }
}
