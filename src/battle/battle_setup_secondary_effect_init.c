#include "fft/battle.h"

void battle_setup_secondary_effect_init(battle_display_unit_t* unit, battle_secondary_effect_init_t* effect) {
    effect->unknown_a4 = 0;
    effect->caster_id = unit->unit_id;
    effect->target_count = 1;
    effect->animate_on_miss = 0;
    effect->target_id = unit->unit_id;
}
