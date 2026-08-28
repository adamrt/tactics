#include "fft/battle.h"

extern battle_stats_t* g_current_attacker;
extern s16 g_current_ability_xa;
extern u8 g_current_ability_element;

void battle_apply_elemental_strengthen(void) {
    if (g_current_attacker->elemental_affinity[4] & g_current_ability_element) {
        g_current_ability_xa = g_current_ability_xa * 5 / 4;
    }
}
