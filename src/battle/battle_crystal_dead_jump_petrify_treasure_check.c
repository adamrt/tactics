#include "fft/battle.h"

s32 battle_crystal_dead_jump_petrify_treasure_check(battle_stats_t* unit) {
    s32 r;
    if (unit->entd_slot == 0xFF)
        return 1;
    /* status 1: crystal 0x40, dead 0x20, jump 0x04; status 2: petrify 0x80, treasure 0x01 */
    if (unit->current_status[0] & 0x64)
        return 1;
    r = unit->current_status[1] & 0x81;
    if (r != 0)
        r = 1;
    return r;
}
