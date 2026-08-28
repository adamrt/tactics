#include "fft/battle.h"

extern battle_misc_data_t* get_unit_misc_data_by_unit_id(u32 unit_id);

u8* battle_get_screen_data_ptr_by_battle_id(u32 battle_id) {
    battle_misc_data_t* unit = get_unit_misc_data_by_unit_id(battle_id & 0xffff);

    if (unit == 0) {
        return 0;
    }
    return (u8*)&unit->screen_x;
}
