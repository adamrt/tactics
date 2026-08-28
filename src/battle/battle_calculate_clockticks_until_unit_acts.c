#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;

s32 battle_calculate_clockticks_until_unit_acts(battle_stats_t* unit) {
    battle_ai_data_t* ai;
    s32 speed;
    s32 ticks;
    s32 rem;

    ai = &g_ai_data_base;
    speed = unit->attributes[2];
    ticks = 0;
    if (speed == 0) {
        return 0x7FFFFFFF;
    }
    if ((*(u16*)&unit->current_status[0] & 0x8140) != 0) {
        return 0x7FFFFFFF;
    }
    /* targeting_flags_2 bit 0x20: dead without Reraise (wiki page 00003578). */
    if ((ai->unit_decisions[unit->entd_slot].targeting_flags_2 >> 5) & 1) {
        return 0x7FFFFFFF;
    }
    if (unit->current_status[3] & 2) {
        ticks = unit->status_ct[6];
    }
    if (unit->ct < 0x64) {
        rem = 0x64 - unit->ct;
        ticks += rem / speed;
        if (rem % speed != 0) {
            ticks += 1;
        }
    }
    if (unit->current_status[0] & 0x20) {
        return ticks;
    }
    if ((unit->current_status[4] & 0x10) == 0) {
        return ticks;
    }
    if (ticks < unit->status_ct[11]) {
        ticks = unit->status_ct[11];
    }
    return ticks;
}
