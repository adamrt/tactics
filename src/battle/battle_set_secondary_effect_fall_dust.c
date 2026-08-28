#include "fft/battle.h"

extern void battle_set_secondary_effect(battle_display_unit_t*, s32);

void battle_set_secondary_effect_fall_dust(battle_display_unit_t* unit) {
    battle_set_secondary_effect(unit, 9);
}
