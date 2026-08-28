#include "fft/battle.h"

extern void battle_setup_secondary_effect_init(battle_display_unit_t*, u8*);
extern void initialize_secondary_effect(s32, u32, u8*);

void battle_set_secondary_effect(battle_display_unit_t* unit, s32 effect_type) {
    u8 data[200];

    battle_setup_secondary_effect_init(unit, data);
    if (unit->battle_data != 0) {
        initialize_secondary_effect(effect_type, unit->battle_data->sprite_palette, data);
    }
}
