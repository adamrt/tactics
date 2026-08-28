#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;

battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id) {
    battle_misc_data_t* unit;

    unit = g_misc_unit_list_head;
    while (unit != 0) {
        if ((unit->battle_data != 0) && (unit->battle_data->misc_unit_id == (battle_id & 0xFFFF))) {
            return unit;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    return 0;
}
