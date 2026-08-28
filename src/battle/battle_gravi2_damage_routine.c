#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;

void battle_gravi2_damage_routine(void) {
    battle_stats_t* target;

    target = g_current_target;
    if (target->hp != 0) {
        g_target_current_action->hp_damage = (s16)(g_current_target->hp - 1);
    } else {
        g_target_current_action->hp_damage = 0;
    }
    g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
}
