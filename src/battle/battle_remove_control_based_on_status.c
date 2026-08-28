#include "fft/battle.h"
#include "psx/types.h"

void battle_remove_control_based_on_status(battle_stats_t* unit) {
    if ((unit->current_status[1] & 0x14) || (unit->current_status[2] & 0xC) || (unit->current_status[4] & 0x20)) {
        unit->team_flags = unit->team_flags & 0xF7;
    } else {
        unit->team_flags = unit->team_flags | (unit->initial_team_flags & 8);
    }
    if ((unit->current_status[4] & 0x20) == 0) {
        unit->team_flags = (unit->team_flags & 0xCF) | (unit->initial_team_flags & BATTLE_TEAM_MASK);
    }
}
