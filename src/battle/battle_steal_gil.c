#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_attacker_current_action;
extern battle_action_data_t* g_target_current_action;

extern s32 battle_get_script_variable(s32 id);
extern void battle_force_attack_miss(void);

void battle_steal_gil(void) {
    battle_stats_t* attacker;
    battle_action_data_t* action;
    battle_action_data_t* target_action;
    battle_action_data_t* other;
    s32 amount;
    s32 available;
    s32 stolen;

    attacker = g_current_attacker;
    amount = attacker->attributes[2] * attacker->level;
    if (!(g_target_unit_data->team_flags & BATTLE_TEAM_MASK)) {
        available = battle_get_script_variable(0x2c);
        if (available < amount) {
            amount = available;
        }
    }
    if (amount == 0) {
        battle_force_attack_miss();
        return;
    }
    action = g_attacker_current_action;
    action->hit = 1;
    other = g_attacker_current_action;
    action->gil_change = (s16)amount;
    other->attack_type = 1;
    /* Read back unsigned (lhu), as the target does. */
    stolen = *(u16*)&g_attacker_current_action->gil_change;
    target_action = g_target_current_action;
    target_action->attack_type = 1;
    target_action->gil_change = (s16)(0 - stolen);
}
