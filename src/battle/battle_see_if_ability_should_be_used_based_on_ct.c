#include "fft/battle.h"
#include "psx/types.h"

extern u8 D_8019F3C5;
extern battle_stats_t battle_stats[];
extern s32 battle_calculate_clockticks_until_unit_acts(battle_stats_t*);
extern s32 battle_status_ct_based_decision(u8, s32);

s32 battle_see_if_ability_should_be_used_based_on_ct(s32 unit_index) {
    s32 min_ct;
    u8 ct;

    ct = D_8019F3C5;
    if (ct != 0) {
        min_ct = battle_calculate_clockticks_until_unit_acts(&battle_stats[unit_index]);
        if (min_ct != 0x7FFFFFFF) {
            if ((s32)ct >= min_ct) {
                return battle_status_ct_based_decision(ct, unit_index);
            }
        }
    }
    return 0;
}
