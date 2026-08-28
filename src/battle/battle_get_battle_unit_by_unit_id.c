#include "fft/battle.h"

extern void find_unit_by_id(s32 unit_id, s32* out_index);
extern s32 func_80180B2C(s32 unit_id);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32 index);
extern s32 battle_get_unit_misc_id_by_battle_id(s32 index);

battle_stats_t* battle_get_battle_unit_by_unit_id(s32 unit_id) {
    s32 index;
    battle_stats_t* stats;
    s32 raid_class;

    find_unit_by_id(unit_id, &index);
    if (index < 0) {
        if ((u32)(unit_id - 1) >= 0x49U) {
            return (battle_stats_t*)-1;
        }
        raid_class = func_80180B2C(unit_id);
        index = raid_class;
        if (raid_class < 0)
            goto ret_neg;
        stats = battle_get_battle_stats_from_battle_id(raid_class);
        if ((u32)(stats->unit_id - 0x78) < 5U) {
            return stats;
        }
        goto ret_neg;
    }
    if (battle_get_unit_misc_id_by_battle_id(index) < 0) {
    ret_neg:
        return (battle_stats_t*)-1;
    }
    return battle_get_battle_stats_from_battle_id(index);
}
