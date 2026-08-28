#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(s32 target);
extern battle_action_data_t* g_target_current_action;
extern s32 g_current_target;
extern s32 g_battle_action_state;

void battle_mp_switch_usability(void) {
    battle_stats_t* unit;
    battle_action_data_t* action;
    battle_action_data_t* action2;

    /* The target reads hp_damage / mp_damage signed (lh). */
    if (*(s16*)&g_target_current_action->hp_damage == 0) {
        return;
    }
    unit = (battle_stats_t*)g_current_target;
    if (unit->mp == 0) {
        return;
    }
    if (battle_chance_to_react(g_current_target) != 0) {
        return;
    }
    if (g_battle_action_state != 0) {
        return;
    }
    action = g_target_current_action;
    action->mp_damage = action->mp_damage + action->hp_damage;
    if (*(s16*)&action->mp_damage >= 0x3E8) {
        action->mp_damage = 0x3E7;
    }
    action2 = g_target_current_action;
    action2->attack_type &= 0x7F;
    action = g_target_current_action;
    action2->hp_damage = 0;
    action->attack_type |= BATTLE_ACTION_TYPE_MP_DAMAGE;
    g_target_current_action->reaction_id = 0x1BD;
}
