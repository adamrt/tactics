#include "fft/battle.h"
#include "fft/data.h"

void main_initialize_unit_position_rewards(battle_stats_t* unit, entd_unit_t* entd) {
    unit->x = entd->x;
    unit->position.bits.y = entd->position.bits.y;
    unit->position.bits.higher_elevation = entd->position.bits.higher_elevation;
    unit->position.bits.facing = entd->position.bits.facing;
    unit->position.bits.flags_12_13 = entd->position.bits.flags_12_13;

    unit->war_trophy = entd->war_trophy;
    unit->bonus_money_modifier = entd->bonus_money_modifier;
}
