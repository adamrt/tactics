#include "fft/battle.h"
#include "psx/types.h"

extern void update_unit_action_statuses(battle_stats_t* unit, s32 action_state);

void battle_disable_acting_statuses(battle_stats_t* unit) {
    update_unit_action_statuses(unit, 0);
}
