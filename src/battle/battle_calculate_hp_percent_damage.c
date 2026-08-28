#include "fft/battle.h"

extern battle_stats_t* g_target_unit_data;
extern u8 g_current_ability_y;
extern battle_action_data_t* g_target_current_action;

void battle_calculate_hp_percent_damage(void) {
    battle_action_data_t* action;
    s32 damage;

    damage = (g_target_unit_data->max_hp * g_current_ability_y + 99) / 100;
    action = g_target_current_action;
    action->attack_type |= BATTLE_ACTION_TYPE_HP_DAMAGE;
    action->hp_damage = damage;
}
