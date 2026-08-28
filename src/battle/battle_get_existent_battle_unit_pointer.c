#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

battle_stats_t* battle_get_existent_battle_unit_pointer(u32 unit_id) {
    battle_stats_t* unit = 0;
    if (unit_id < 0x15U) {
        unit = &battle_stats[unit_id];
        if (unit->entd_slot == 0xFF) {
            unit = 0;
        }
    }
    return unit;
}
