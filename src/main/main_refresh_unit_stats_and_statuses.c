#include "fft/battle.h"
#include "psx/types.h"

extern void update_unit_stats_statuses_and_equipment(battle_stats_t*, s32, s32);

void main_refresh_unit_stats_and_statuses(battle_stats_t* unit) {
    update_unit_stats_statuses_and_equipment(unit, 0, 0);
}
