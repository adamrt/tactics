#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_target;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_base_hit;
extern s32 battle_check_if_unit_can_evade(battle_stats_t*);

/* When the target has the Abandon reaction and the initial hit-chance
   check fails, halve the evasion counter and swap in the "abandoned"
   ability id (0x1C1) so the miss animation plays with that string. */
void battle_abandon_calculation(void) {
    u8* evade_counter;
    if ((battle_check_if_unit_can_evade(g_current_target) == 0) && (g_current_target->reaction_abilities[3] & 0x10)) {
        evade_counter = &g_current_ability_base_hit;
        *evade_counter = *evade_counter >> 1;
        g_target_current_action->reaction_id = 0x1C1;
    }
}
