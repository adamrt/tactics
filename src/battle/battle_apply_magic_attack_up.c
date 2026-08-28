#include "fft/battle.h"

extern battle_stats_t* g_current_attacker;
extern s16 g_current_ability_xa;

void battle_apply_magic_attack_up(void) {
    if (g_current_attacker->support_abilities[1] & 4) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 4 / 3;
    }
}
