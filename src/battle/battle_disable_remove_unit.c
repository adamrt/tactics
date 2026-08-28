#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

s32 battle_disable_remove_unit(s32 unit_id) {
    battle_stats_t* unit = &battle_stats[unit_id];
    if (unit->entd_slot != 0xFF) {
        unit->entd_slot = 0xFF;
        unit->existence = 0x80;
    }
    return 0;
}
