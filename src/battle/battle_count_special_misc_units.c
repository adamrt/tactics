#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;

s32 battle_count_special_misc_units(void) {
    battle_misc_data_t* unit;
    s32 count;

    count = 0;
    unit = g_misc_unit_list_head;
    while (unit != 0) {
        if (unit->spritesheet_id == 0x9B) {
            count++;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    return count;
}
