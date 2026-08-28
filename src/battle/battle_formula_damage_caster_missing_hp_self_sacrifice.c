#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_stats_t* g_current_attacker;
extern battle_action_data_t* g_target_current_action;
extern void battle_apply_status(void);

/* Formula 0x52: damage (CasMaxHP - CasCurHP), 100% status; caster in AoE takes its own current HP as damage. */
void battle_formula_damage_caster_missing_hp_self_sacrifice(void) {
    if (g_target_unit_data != g_current_attacker) {
        battle_stats_t* caster = g_current_attacker;
        battle_action_data_t* action = g_target_current_action;

        action->hp_damage = caster->max_hp - caster->hp;
        action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    } else {
        battle_action_data_t* action = g_target_current_action;

        action->hp_damage = g_target_unit_data->hp;
        action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    }
    if (g_target_unit_data != g_current_attacker) {
        battle_apply_status();
    }
}
