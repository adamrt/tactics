#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern s32 battle_status_checks(battle_stats_t*);

s32 battle_change_of_turn_check(s32 unit_id) {
    battle_stats_t* unit = &battle_stats[unit_id];
    if (unit->entd_slot == 0xFF) {
        return 1;
    }
    if (!(battle_status_checks(unit) & 0xD)) {
        return unit->has_turn == 0;
    }
    unit->has_turn = 0;
    return 1;
}
