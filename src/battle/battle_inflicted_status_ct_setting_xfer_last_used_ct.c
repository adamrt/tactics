#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern s32 main_set_status_ct(battle_stats_t* unit, s32 status_id, s32 removing);
extern void battle_enable_special_status_flags(s32 a, s32 b, s32 c);
extern void main_store_current_status(battle_stats_t* unit);

void battle_inflicted_status_ct_setting_xfer_last_used_ct(s32 unit_idx) {
    battle_stats_t* unit;
    s32 i;
    s32 mask;
    s32 idx;

    unit = &battle_stats[unit_idx];
    for (i = 0; i < 40; i++) {
        idx = i / 8;
        mask = 0x80 >> (i & 7);
        if (unit->action.status_removal[idx] & mask) {
            unit->inflicted_status[idx] = (u8)(unit->inflicted_status[idx] & ~mask);
            if (main_set_status_ct(unit, i, 1) == 0) {
                battle_enable_special_status_flags(i + 1, 0, unit_idx);
            }
        }
    }
    main_store_current_status(unit);
}
