#include "fft/battle.h"

extern battle_misc_data_t* g_last_unit_misc_data;

s32 battle_get_unit_misc_id_by_battle_id(u32 battle_id) {
    battle_misc_data_t* unit = g_last_unit_misc_data;

    while (unit != 0) {
        battle_stats_t* battle_data = unit->battle_data;

        if (battle_data != 0 && battle_data->misc_unit_id == battle_id) {
            return unit->unit_id;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    return -1;
}
