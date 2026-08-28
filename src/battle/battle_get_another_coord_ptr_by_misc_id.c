#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void main_pointer_exception_handler(s32 error_code);

s16* battle_get_another_coord_ptr_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit == 0) {
        main_pointer_exception_handler(12);
        return 0;
    }
    return &unit->effect_vector_2_x;
}
