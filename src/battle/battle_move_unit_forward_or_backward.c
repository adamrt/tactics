#include "fft/battle.h"
#include "psx/types.h"

void battle_move_unit_forward_or_backward(battle_misc_data_t* unit, s32 delta) {
    switch (unit->facing & (BATTLE_FACING_EAST | BATTLE_FACING_NORTH)) {
    case BATTLE_FACING_NORTH:
        unit->effect_vector_y += (s8)delta;
        break;
    case BATTLE_FACING_SOUTH:
        unit->effect_vector_y -= (s8)delta;
        break;
    case BATTLE_FACING_WEST:
        unit->effect_vector_x -= (s8)delta;
        break;
    case BATTLE_FACING_EAST:
        unit->effect_vector_x += (s8)delta;
        break;
    }
}
