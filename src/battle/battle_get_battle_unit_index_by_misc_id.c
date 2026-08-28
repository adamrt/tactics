#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void main_pointer_exception_handler(s32 error_code);

s32 battle_get_battle_unit_index_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit != 0) {
        battle_stats_t* battle_data = unit->battle_data;

        if (battle_data != 0) {
            return battle_data->misc_unit_id;
        }
    } else {
        main_pointer_exception_handler(12);
    }
    return -1;
}
