#include "fft/battle.h"

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);

s32 battle_has_status_effect_for_status_window(s32 unit_id) {
    battle_stats_t* unit;
    s32 index;

    unit = get_battle_stats_pointer(unit_id);
    for (index = 0; index < 5; index++) {
        if (unit->current_status[index] != 0) {
            return 1;
        }
    }
    return 0;
}
