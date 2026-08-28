#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_action_data_t* g_attacker_current_action;
extern void func_8018BA44(u16 arg0);

/* Convert the pending MP-cost field into an actual MP recovery event on
   the current action and mirror the amount onto the linked reaction
   record so the animation reports "MP restored". */
void battle_mp_recovery_routine(void) {
    u16 mp_amount;
    battle_action_data_t* action;
    battle_action_data_t* action_after;

    action = g_target_current_action;
    mp_amount = action->hp_damage;
    action->hp_damage = 0;
    action->attack_type = BATTLE_ACTION_TYPE_MP_DAMAGE;
    action->mp_damage = mp_amount;
    func_8018BA44(mp_amount);
    action_after = g_target_current_action;
    if (action_after->hit != 0) {
        battle_action_data_t* reaction = g_attacker_current_action;
        reaction->mp_healing = action_after->mp_damage;
        reaction->attack_type = BATTLE_ACTION_TYPE_MP_HEALING;
        g_attacker_current_action->hit = 1;
    }
}
