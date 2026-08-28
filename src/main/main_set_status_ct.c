#include "fft/battle.h"
#include "fft/status.h"
#include "psx/types.h"

s32 main_set_status_ct(battle_stats_t* unit, s32 status_id, s32 removing) {
    battle_stats_t* stats = unit;
    s32 ct_index;
    s32 stored_index;

    if (status_id == 2) {
        if ((stats->team_flags & BATTLE_TEAM_FLAG_IMMORTAL) || (stats->unit_flags & (BATTLE_UNIT_FLAG_SAVE_FORMATION | BATTLE_UNIT_FLAG_LOAD_FORMATION))) {
            stats->death_counter = 0xff;
        } else {
            stats->death_counter = 3;
        }
    }

    ct_index = status_id - 24;
    if ((u32)ct_index >= 16) {
        return 0;
    }
    stored_index = ct_index;
    if (removing) {
        stats->status_ct[stored_index] = 0;
        return 0;
    }
    if ((stored_index == 15) && (stats->status_ct[15] != 0)) {
        return -1;
    }
    stats->status_ct[stored_index] = g_status_effect_data[status_id].ct;
    return 0;
}
