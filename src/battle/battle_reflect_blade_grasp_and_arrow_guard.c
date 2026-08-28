#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_action_type;
extern u8 g_current_ability_formula;
extern battle_stats_t* g_current_target;
extern u16 g_current_ability_reaction_id;
extern battle_action_data_t* g_target_current_action;

extern s32 battle_reaction_check(battle_stats_t* unit);
extern void battle_reflect_reaction(void);
extern s32 battle_check_if_unit_can_react(battle_stats_t* unit);
extern s32 battle_check_if_unit_can_evade(battle_stats_t* unit);
extern void battle_blade_grasp_usability(void);
extern void battle_arrow_guard_usability(void);

void battle_reflect_blade_grasp_and_arrow_guard(void) {
    u8 reaction_flags;

    if (g_battle_action_type != 0) {
        return;
    }
    if (g_current_ability_formula == 7) {
        return;
    }
    if (battle_reaction_check(g_current_target) == 1) {
        return;
    }
    if ((g_current_target->current_status[4] & 2) && g_current_ability_reaction_id == 0) {
        battle_reflect_reaction();
    }
    /* reaction_id is loaded signed (lh) here. */
    if (*(s16*)&g_target_current_action->reaction_id != 0) {
        return;
    }
    if (battle_check_if_unit_can_react(g_current_target) != 0) {
        return;
    }
    if (battle_check_if_unit_can_evade(g_current_target) != 0) {
        return;
    }
    reaction_flags = g_current_target->reaction_abilities[3];
    if (reaction_flags & 4) {
        battle_blade_grasp_usability();
        return;
    }
    if (reaction_flags & 2) {
        battle_arrow_guard_usability();
    }
}
