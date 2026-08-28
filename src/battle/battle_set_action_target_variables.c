#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_target_id;
extern void battle_current_action_data_nulling(battle_action_data_t*);

void battle_set_action_target_variables(battle_stats_t* unit) {
    battle_action_data_t* action = &unit->action;
    g_target_unit_data = unit;
    g_target_current_action = action;
    g_current_ability_target_id = unit->misc_unit_id;
    battle_current_action_data_nulling(action);
}
