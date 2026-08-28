#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[21];

s32 battle_erase_unit_set_to_be_removed_from_party(s32 unit_id) {
    battle_stats_t* unit = &battle_stats[unit_id];
    unit->entd_slot = 0xFF;
    unit->existence = 2;
    return 0;
}
