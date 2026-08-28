#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern u8 g_ai_unit_enemy_flag;
extern u8 g_ai_acting_unit_remaining_clockticks;

extern s32 battle_check_if_status_should_can_be_added(s32, battle_stats_t*, s32);
extern s32 battle_calculate_clockticks_until_unit_acts(battle_stats_t*);

s32 battle_check_if_regen_charm_dm_reraise_da_can_be_inflicted(s32 unit_id) {
    battle_stats_t* unit;
    s32 limit;

    if ((&g_ai_unit_enemy_flag)[unit_id * 0x10] == 0) {
        goto ret1;
    }
    unit = &battle_stats[unit_id];
    limit = g_ai_acting_unit_remaining_clockticks;
    if (limit < battle_calculate_clockticks_until_unit_acts(unit)) {
        goto ret1;
    }
    if (battle_check_if_status_should_can_be_added(g_ai_acting_unit_remaining_clockticks, unit, 0x1E) != 0) {
        goto ret1;
    }
    if (battle_check_if_status_should_can_be_added(g_ai_acting_unit_remaining_clockticks, unit, 0x25) != 0) {
        goto ret1;
    }
    if (battle_check_if_status_should_can_be_added(g_ai_acting_unit_remaining_clockticks, unit, 0x23) != 0) {
        goto ret1;
    }
    if (battle_check_if_status_should_can_be_added(g_ai_acting_unit_remaining_clockticks, unit, 0x15) == 0) {
        goto last;
    }
ret1:
    return 1;
last:
    return battle_check_if_status_should_can_be_added(g_ai_acting_unit_remaining_clockticks, unit, 0x22) != 0;
}
