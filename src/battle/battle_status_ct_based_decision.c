#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

extern s32 battle_check_if_status_should_can_be_added(s32, battle_stats_t*, s32);
extern s32 battle_calculate_clockticks_until_unit_acts(battle_stats_t*);

s32 battle_status_ct_based_decision(s32 limit, s32 unit_id) {
    battle_stats_t* unit = &battle_stats[unit_id];

    if (unit->entd_slot == 0xFF) {
        goto ret0;
    }
    if (unit->attributes[2] == 0) {
        return 0;
    }
    if ((*(u16*)&unit->current_status[0] & 0x8140) != 0) {
        return 0;
    }
    if (battle_check_if_status_should_can_be_added(limit, unit, 0x1E) != 0) {
        return 0;
    }
    if (battle_check_if_status_should_can_be_added(limit, unit, 0x24) != 0) {
        return 0;
    }
    if (battle_check_if_status_should_can_be_added(limit, unit, 0x23) != 0) {
        return 0;
    }
    if ((unit->current_status[0] & 0x20) == 0) {
        return 1;
    }
    if ((unit->current_status[2] & 0x20) == 0) {
        return 0;
    }
    if (limit >= battle_calculate_clockticks_until_unit_acts(unit)) {
        goto ret1;
    }
ret0:
    return 0;
ret1:
    return 1;
}
