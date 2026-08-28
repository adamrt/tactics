#include "fft/battle.h"

extern battle_stats_t* volatile g_current_target;
extern s16 g_current_ability_xa;

void battle_target_xa_affecting_statuses(void) {
    battle_stats_t* target;

    if (g_current_target->current_status[3] & 0x20) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 2 / 3;
    }

    target = g_current_target;
    if ((target->current_status[4] & 0x10) || (target->current_status[0] & 8)) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 3 / 2;
    }

    if (g_current_target->current_status[2] & 6) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 3 / 2;
    }
}
