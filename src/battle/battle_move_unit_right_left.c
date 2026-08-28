#include "fft/battle.h"

void battle_move_unit_right_left(battle_misc_data_t* unit, s8 delta) {
    s16* p;
    switch (unit->facing & 0xC00) {
    case 0x800:
        p = &unit->effect_vector_x;
        *p = *p + delta;
        return;
    case 0x0:
        p = &unit->effect_vector_x;
        *p = *p - delta;
        return;
    case 0x400:
        p = &unit->effect_vector_y;
        *p = *p + delta;
        return;
    case 0xC00:
        p = &unit->effect_vector_y;
        *p = *p - delta;
        return;
    }
}
