#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_action_data_t* g_attacker_current_action;
extern void battle_current_action_data_nulling(battle_action_data_t* action);

void battle_action_data_nulling(void) {
    battle_current_action_data_nulling(g_target_current_action);
    battle_current_action_data_nulling(g_attacker_current_action);
    g_attacker_current_action->hit = 0;
}
