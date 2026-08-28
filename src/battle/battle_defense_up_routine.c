#include "fft/battle.h"

extern battle_stats_t* g_current_target;
extern s16 g_current_ability_xa;

void battle_defense_up_routine(void) {
    s16* p;
    /* Battle Stats 0x90 bit 0x08 is Defense Up (wiki page 00000307). */
    if (g_current_target->support_abilities[1] & 8) {
        p = &g_current_ability_xa;
        *p = (*p * 2) / 3;
    }
}
