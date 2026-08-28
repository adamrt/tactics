#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

void battle_flip_misc_data_move_flag_bit_3(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit != 0) {
        unit->movement.word |= 0x04000000;
    }
}
