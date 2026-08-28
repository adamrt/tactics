#include "fft/battle.h"
#include "psx/types.h"

extern void main_initialize_status_ct(battle_stats_t*);
extern void main_update_unit_status_flags_and_ct(battle_stats_t*);

void main_initialize_unit_status(battle_stats_t* unit) {
    s32 status_set;

    for (status_set = 0; status_set < 5; status_set++) {
        unit->inflicted_status[status_set] = unit->current_status[status_set] & ~unit->innate_status[status_set];
    }
    main_initialize_status_ct(unit);
    main_update_unit_status_flags_and_ct(unit);
}
