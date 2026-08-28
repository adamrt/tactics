#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;

/* Restore the target to full HP and MP (100% HP/MP healing). */
void battle_apply_full_hp_mp_heal(void) {
    battle_stats_t* unit = g_target_unit_data;
    battle_action_data_t* action = g_target_current_action;

    action->hp_damage = unit->max_hp;
    action->mp_healing = unit->max_mp;
    action->attack_type = 0x90;
}
