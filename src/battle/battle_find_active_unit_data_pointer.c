#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

battle_stats_t* battle_find_active_unit_data_pointer(void) {
    s32 i = 0;
    battle_stats_t* unit = battle_stats;
    do {
        if (unit->has_turn != 0) {
            return unit;
        }
        i++;
        unit++;
    } while (i < 0x15);
    return (battle_stats_t*)0;
}
