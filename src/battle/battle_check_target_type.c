#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern battle_stats_t battle_stats[];

/* 1 when the unit is untargetable or dead per its AI decision record;
 * otherwise the top bit of its second current-status byte. */
s32 battle_check_target_type(s32 unit_id) {
    u8 flags = g_ai_data_base.unit_decisions[unit_id].targeting_flags_2;

    if (((flags >> 4) & 1) || ((flags >> 5) & 1)) {
        return 1;
    }
    return battle_stats[unit_id].current_status[1] >> 7;
}
