#include "fft/battle.h"

extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern battle_action_data_t* g_target_current_action;

void battle_store_xa_times_ya_damage(void) {
    u32 damage;
    battle_action_data_t* action;

    damage = g_current_ability_xa * g_current_ability_ya;
    action = g_target_current_action;
    action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    action->hp_damage = damage;
}
