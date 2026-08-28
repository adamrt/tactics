#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(void* a, void* b);
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;

void battle_distribute_usability(void) {
    battle_stats_t* target = g_current_target;
    battle_action_data_t* action = g_target_current_action;
    /* hp_healing is read signed (lh) here. */
    s32 excess = *(s16*)&action->hp_healing - (s32)(target->max_hp - target->hp);
    if (excess > 0 && battle_chance_to_react(target, target) == 0) {
        g_target_current_action->last_received_attack = (s16)excess;
        g_target_current_action->reaction_id = 0x1BC;
    }
}
