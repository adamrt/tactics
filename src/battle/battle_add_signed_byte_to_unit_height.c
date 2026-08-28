#include "fft/battle.h"
#include "psx/types.h"

void battle_add_signed_byte_to_unit_height(battle_misc_data_t* unit, s32 delta) {
    unit->effect_vector_z += (s8)delta;
}
