#include "fft/battle.h"

extern battle_stats_t* volatile g_current_attacker;
extern battle_stats_t* volatile g_current_target;
extern u8* g_target_current_action;
extern u8 g_current_ability_target_faith;
extern u8 g_current_ability_attacker_faith;

void battle_faith_calculation(void) {
    u8* act;

    if (g_current_attacker->current_status[4] & 0x80) {
        g_current_ability_attacker_faith = 100;
    }
    if (g_current_attacker->current_status[4] & 0x40) {
        g_current_ability_attacker_faith = 0;
    }
    if (g_current_target->current_status[4] & 0x80) {
        g_current_ability_target_faith = 100;
    }
    if (g_current_target->current_status[4] & 0x40) {
        g_current_ability_target_faith = 0;
    }

    act = g_target_current_action;
    *(s16*)(act + 4) = *(s16*)(act + 4) * g_current_ability_target_faith * g_current_ability_attacker_faith / 10000;
}
