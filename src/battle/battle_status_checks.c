#include "fft/battle.h"
#include "psx/types.h"

extern s32 main_unit_has_status_in_set(battle_stats_t* unit, s32 set);

s32 battle_status_checks(battle_stats_t* unit) {
    s32 status1;
    s32 status4;
    s32 status5;
    s32 flags;

    if (unit->entd_slot == 0xff) {
        return 1;
    }
    if (main_unit_has_status_in_set(unit, 3) != 0) {
        return 1;
    }
    if ((unit->mount_info & 0x40) != 0) {
        return 1;
    }
    status1 = unit->current_status[0];
    status4 = unit->current_status[3];
    status5 = unit->current_status[4];
    if ((status1 & 0x20) != 0) {
        return 6;
    }
    flags = -(s32)((status5 & 0x10) != 0) & 0xa;
    if ((status4 & 8) != 0) {
        flags |= 0x10;
    }
    if ((status4 & 4) != 0) {
        flags |= 0x20;
    }
    return flags;
}
