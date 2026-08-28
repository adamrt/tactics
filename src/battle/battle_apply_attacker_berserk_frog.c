#include "fft/battle.h"

extern battle_stats_t* volatile g_current_attacker;
extern s16 g_current_ability_xa;

void battle_apply_attacker_berserk_frog(void) {
    if (g_current_attacker->current_status[2] & 8) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 3 / 2;
    }
    if (g_current_attacker->current_status[2] & 2) {
        g_current_ability_xa = 1;
    }
}
