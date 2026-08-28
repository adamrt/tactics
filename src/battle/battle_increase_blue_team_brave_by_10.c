#include "fft/battle.h"

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);

void battle_increase_blue_team_brave_by_10(void) {
    battle_stats_t* unit;
    s32 unit_id;

    for (unit_id = 0; unit_id < 21; unit_id++) {
        unit = get_battle_stats_pointer(unit_id);
        if ((unit->team_flags & BATTLE_TEAM_MASK) == BATTLE_TEAM_BLUE) {
            unit->brave += 10;
            if (unit->brave >= 100) {
                unit->brave = 100;
            }
        }
    }
}
