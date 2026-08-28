#include "fft/battle.h"
#include "psx/types.h"

void require_copy_battle_stats_to_status_gauges(battle_stats_t* unit, u8* output) {
    u16 maximum_hp;
    u16 maximum_mp;
    u8 ct;

    *(s16*)(output + 0) = unit->level;
    *(s16*)(output + 2) = 0;
    if (unit->initial_team_flags & 0x30) {
        *(s16*)(output + 2) = 1;
    }
    if (!(unit->initial_team_flags & 0x38)) {
        *(s16*)(output + 2) = 2;
    }
    if (unit->auto_battle_setting != 0) {
        *(s16*)(output + 2) = 3;
    }
    *(s16*)(output + 8) = unit->experience;
    maximum_hp = unit->max_hp;
    *(u16*)(output + 0x10) = maximum_hp;
    if (maximum_hp == 0) {
        *(u16*)(output + 0x10) = maximum_hp + 1;
    }
    *(u16*)(output + 0xc) = unit->hp;
    *(s16*)(output + 0xe) = 0;
    maximum_mp = unit->max_mp;
    *(u16*)(output + 0x16) = maximum_mp;
    if (maximum_mp == 0) {
        *(u16*)(output + 0x16) = maximum_mp + 1;
    }
    *(u16*)(output + 0x12) = unit->mp;
    *(s16*)(output + 0x14) = 0;
    *(s16*)(output + 0x1c) = 100;
    ct = unit->ct;
    *(s16*)(output + 0xa) = 0;
    *(s16*)(output + 4) = 0;
    *(s16*)(output + 6) = 0;
    *(s16*)(output + 0x18) = ct;
}
