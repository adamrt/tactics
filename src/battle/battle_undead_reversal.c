#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_target;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_canceled_statuses;

void battle_undead_reversal(void) {
    battle_action_data_t* action;
    battle_action_data_t* action_again;
    u16 hp_damage;
    if (g_current_target->current_status[0] & 0x10) {
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
        g_current_ability_canceled_statuses = 0;
        return;
    }
    action = g_target_current_action;
    action->attack_type = action->attack_type & 0x7F;
    hp_damage = action->hp_damage;
    action_again = g_target_current_action;
    action->hp_damage = 0;
    action->hp_healing = hp_damage;
    action_again->attack_type = action_again->attack_type | BATTLE_ACTION_TYPE_HP_HEALING;
}
