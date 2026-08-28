#include "fft/battle.h"

extern void initialize_status(battle_stats_t* unit);

void main_initialize_unit_status_and_rewards(battle_stats_t* unit, s32 clear_rewards) {
    if (unit->attributes[2] == 0) {
        unit->attributes[2] = 1;
    }
    if (clear_rewards != 0) {
        unit->war_trophy = 0;
        unit->bonus_money_modifier = 0;
    }
    initialize_status(unit);
}
