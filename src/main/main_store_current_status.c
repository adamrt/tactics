#include "fft/battle.h"

void main_store_current_status(battle_stats_t* unit) {
    battle_stats_t* unit_data = unit;
    s32 status_set;

    for (status_set = 0; status_set < 5; status_set++) {
        unit_data->current_status[status_set] = unit_data->innate_status[status_set] | unit_data->inflicted_status[status_set];
    }
}
