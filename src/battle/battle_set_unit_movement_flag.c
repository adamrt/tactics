#include "fft/battle.h"

void battle_set_unit_movement_flag(battle_misc_data_t* unit) {
    if (unit->mount_byte == 0) {
        return;
    }
    unit->movement_path[unit->movement_path_offset] |= 0x10;
}
