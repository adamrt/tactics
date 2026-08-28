#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

s32 battle_unit_exists_checks(s32 unit_id) {
    battle_stats_t* unit;

    unit = &battle_stats[unit_id];
    if (unit->entd_slot == 0xFF)
        return -1;
    if (unit->formation_index == 0xFF)
        return -1;
    unit->entd_slot = 0xFF;
    unit->existence = 2;
    return 0;
}
