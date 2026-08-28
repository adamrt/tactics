#include "fft/battle.h"

extern u8 g_ability_ct_data[];

void main_transfer_last_ability_ct(battle_stats_t* unit) {
    s32 ability_id = unit->last_ability_id;

    unit->ability_ct = g_ability_ct_data[ability_id * 14] & 0x7f;
}
