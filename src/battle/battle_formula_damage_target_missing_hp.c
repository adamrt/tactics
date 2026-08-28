#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;

/* Formula 0x45: damage equal to the target's missing HP (MaxHP - CurHP). */
void battle_formula_damage_target_missing_hp(void) {
    battle_stats_t* unit = g_target_unit_data;
    battle_action_data_t* action = g_target_current_action;

    action->hp_damage = unit->max_hp - unit->hp;
    action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
}
