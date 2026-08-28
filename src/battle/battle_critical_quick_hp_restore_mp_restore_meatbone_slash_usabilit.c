#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;
extern s32 battle_chance_to_react(battle_stats_t* unit);

void battle_critical_quick_hp_restore_mp_restore_meatbone_slash_usabilit(s16 reaction_id) {
    battle_stats_t* unit;

    unit = g_target_unit_data;
    if ((unit->current_status[2] & 1) && (g_target_current_action->attack_type & BATTLE_ACTION_TYPE_HP_DAMAGE) && battle_chance_to_react(unit) == 0) {
        g_target_current_action->reaction_id = reaction_id;
    }
}
