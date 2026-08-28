#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s16 battle_get_facing_quadrant_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        return ((s16)unit->facing / 0x400) % 4;
    }
    return -1;
}
