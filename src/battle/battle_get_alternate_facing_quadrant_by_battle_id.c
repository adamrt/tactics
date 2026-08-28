#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);

s16 battle_get_alternate_facing_quadrant_by_battle_id(u32 battle_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_battle_id(battle_id & 0xffff);
    if (unit != 0) {
        return *(s16*)((u8*)unit + 0x6c) % 4;
    }
    return -1;
}
