#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(const battle_stats_t* unit);
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;
extern s32 g_battle_action_state;
extern u8 g_current_ability_flags4;

void battle_blade_grasp_usability(void) {
    battle_stats_t* attacker;
    battle_action_data_t* target;

    if ((g_current_ability_flags4 & 0x10) == 0)
        return;
    attacker = g_current_target;
    target = g_target_current_action;
    /* Halfword store covers attack_accuracy and the pad byte after it. */
    target->attack_accuracy = (s16)(0x64 - attacker->brave);
    if (battle_chance_to_react(attacker) != 0)
        return;
    if (g_battle_action_state != 0)
        return;
    g_target_current_action->hit = 0;
    g_target_current_action->miss_type = 0xB;
    g_target_current_action->reaction_id = 0x1C3;
}
