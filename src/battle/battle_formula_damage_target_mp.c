#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy_no_elemental(void);

void battle_formula_damage_target_mp(void) {
    battle_stats_t* target;
    battle_action_data_t* action;
    u16 mp;

    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy_no_elemental() == 0) {
            target = g_target_unit_data;
            action = g_target_current_action;
            mp = target->mp;
            action->attack_type = BATTLE_ACTION_TYPE_MP_DAMAGE;
            action->mp_damage = mp;
        }
    }
}
