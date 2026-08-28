#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;

/* Formula 0x44: damage equal to the target's current MP. */
void battle_formula_damage_target_current_mp(void) {
    u16 mp = g_target_unit_data->mp;
    battle_action_data_t* action = g_target_current_action;
    action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    action->hp_damage = mp;
}
