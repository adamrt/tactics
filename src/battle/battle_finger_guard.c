#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_check_if_unit_can_react_1(battle_stats_t* unit);
extern s32 battle_chance_to_react(const battle_stats_t* unit);
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;
extern s32 g_battle_action_state;

void battle_finger_guard(void) {
    battle_stats_t* unit;
    s32 chance;

    if (battle_check_if_unit_can_react_1(g_current_target) != 0)
        return;
    unit = g_current_target;
    if ((unit->reaction_abilities[3] & 0x20) == 0)
        return;
    chance = 0x64 - unit->brave;
    /* The target stores the accuracy as a halfword (0x2a..0x2b). */
    g_target_current_action->attack_accuracy = (s16)chance;
    if (chance != 0) {
        if (battle_chance_to_react(unit) != 0)
            return;
        if (g_battle_action_state != 0)
            return;
    }
    g_target_current_action->hit = 0;
    g_target_current_action->reaction_id = 0x1C0;
    g_target_current_action->miss_type = 0xB;
}
