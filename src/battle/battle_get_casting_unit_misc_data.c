#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;
extern s32 g_battle_casting_unit_id;

battle_misc_data_t* battle_get_casting_unit_misc_data(void) {
    battle_misc_data_t* unit;
    s32 casting_unit_id;

    unit = g_misc_unit_list_head;
    if (unit != 0) {
        casting_unit_id = g_battle_casting_unit_id;
        do {
            if (unit->unit_id == casting_unit_id) {
                return unit;
            }
            unit = (battle_misc_data_t*)unit->previous;
        } while (unit != 0);
    }
    return 0;
}
