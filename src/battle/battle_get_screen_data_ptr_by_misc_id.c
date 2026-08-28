#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

u8* battle_get_screen_data_ptr_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit == 0) {
        return 0;
    }
    return (u8*)&unit->screen_x;
}
