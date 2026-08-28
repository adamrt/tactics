#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s32 battle_reset_unit_graphic_trigger(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit != 0) {
        /* Halfword store covering ability_in_use (0x0a) and the pad byte. */
        *(u16*)&unit->ability_in_use = 0;
        unit->sprite_graphic_trigger = 0;
        return 1;
    }
    return 0;
}
