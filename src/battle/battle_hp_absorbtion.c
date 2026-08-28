#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern battle_action_data_t* g_attacker_current_action;

extern void func_8018BA44(void);

void battle_hp_absorbtion(void) {
    battle_action_data_t* action;
    battle_action_data_t* attacker;
    battle_action_data_t* action2;
    battle_action_data_t* action3;
    battle_action_data_t* attacker2;
    u16 amount;

    if (g_target_unit_data->current_status[0] & 0x10) {
        func_8018BA44();
        action = g_target_current_action;
        if (action->hit != 0) {
            attacker = g_attacker_current_action;
            attacker->hp_damage = action->hp_damage;
            attacker->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
            g_attacker_current_action->hit = 1;
            action2 = g_target_current_action;
            amount = action2->hp_damage;
            action2->hp_damage = 0;
            action2->attack_type = BATTLE_ACTION_TYPE_HP_HEALING;
            action2->hp_healing = amount;
        }
        return;
    }
    func_8018BA44();
    action3 = g_target_current_action;
    if (action3->hit != 0) {
        attacker2 = g_attacker_current_action;
        attacker2->hp_healing = action3->hp_damage;
        attacker2->attack_type = BATTLE_ACTION_TYPE_HP_HEALING;
        g_attacker_current_action->hit = 1;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    }
}
