#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[21];

s32 battle_set_unit_cannot_exist_return_r2_0(s32 unit_index) {
    battle_stats_t* unit;
    unit = &battle_stats[unit_index];
    unit->entd_slot = 0xFF;
    unit->existence = 0;
    return 0;
}
