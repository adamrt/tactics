#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void main_pointer_exception_handler(s32 error_code);

s32 battle_unit_moving_check_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit == 0) {
        main_pointer_exception_handler(12);
        return 0;
    }
    return unit->movement_path_count != 0;
}
