#include "fft/battle.h"

extern void battle_set_secondary_effect(battle_display_unit_t*, s32);

void battle_set_secondary_effect_death_smoke(battle_display_unit_t* unit) {
    battle_set_secondary_effect(unit, 0xc);
}
