#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[21];
extern void update_unit_action_statuses(battle_stats_t* unit, s32 action_state);

s32 battle_inflict_defending_to_battle_id(s32 unit_id) {
    update_unit_action_statuses(&battle_stats[unit_id], 7);
    return 0;
}
