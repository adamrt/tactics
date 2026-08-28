#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s16 battle_get_facing_field_0x6e_nibble_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        return *(s16*)((u8*)unit + 0x6e) % 0x10;
    }
    return -1;
}
