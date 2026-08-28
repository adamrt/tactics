#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_attacker;
extern battle_action_data_t* g_attacker_current_action;

extern void battle_apply_full_hp_mp_heal(void);
extern void battle_undead_reversal(void);
extern void battle_force_attack_miss(void);
extern void func_80187F24(battle_stats_t* attacker, battle_action_data_t* action);

void battle_formula_raise_level_by_one_add_status_on_caster(void) {
    battle_action_data_t* action;
    battle_stats_t* saved_unit;
    battle_action_data_t* saved_action;
    battle_stats_t* attacker;
    battle_action_data_t* attacker_action;
    s32 one;

    battle_apply_full_hp_mp_heal();
    battle_undead_reversal();
    one = 1;
    if (g_target_unit_data->level >= 0x63) {
        g_target_current_action->attack_type = 0;
        battle_force_attack_miss();
        return;
    }
    action = g_target_current_action;
    action->attack_type = (u8)one;
    saved_unit = g_target_unit_data;
    saved_action = g_target_current_action;
    attacker = g_current_attacker;
    attacker_action = g_attacker_current_action;
    /* The target stores special_effect/special_flags_2 as one halfword. */
    action->special_effect = 0x80;
    g_target_unit_data = attacker;
    g_target_current_action = attacker_action;
    attacker_action->hit = (u8)one;
    func_80187F24(attacker, action);
    g_target_unit_data = saved_unit;
    g_target_current_action = saved_action;
}
