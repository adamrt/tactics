#include "fft/battle.h"

extern u8 g_status_sets[];

s32 main_unit_has_status_in_set(const battle_stats_t* unit, u32 status_set_index) {
    const u8* status_set = g_status_sets;
    s32 index = 0;

    status_set += status_set_index * 5;

    do {
        if ((unit->current_status[index] & status_set[index]) != 0) {
            return 1;
        }
        index++;
    } while (index < 5);
    return 0;
}
