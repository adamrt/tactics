#include "fft/battle.h"

extern void battle_setup_secondary_effect_init(battle_display_unit_t*, u8*);

void battle_call_secondary_effect_init(battle_display_unit_t* unit) {
    u8 data[200];

    battle_setup_secondary_effect_init(unit, data);
    unit->centre_tile_offset = 0x3b;
}
