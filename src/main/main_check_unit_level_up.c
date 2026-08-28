#include "fft/battle.h"
#include "psx/types.h"

extern void main_apply_unit_level_growth(battle_stats_t*, s32);

s32 main_check_unit_level_up(battle_stats_t* unit) {
    u8 level;

    if (unit->experience < 100) {
        return 0;
    }

    level = unit->level;
    if (level >= 99) {
        unit->experience = 99;
        return 0;
    }

    main_apply_unit_level_growth(unit, 0);
    unit->experience = 0;
    unit->level = level + 1;
    return 1;
}
