#include "fft/battle.h"

extern battle_misc_data_t* g_last_unit_misc_data;
extern void battle_reset_unit_graphic_trigger(u32 misc_id);

void battle_reset_jumping_unit_graphic_triggers(void) {
    battle_misc_data_t* unit = g_last_unit_misc_data;

    while (unit != 0) {
        if ((unit->status_flags_5_6 & 0x40) != 0) {
            battle_reset_unit_graphic_trigger(unit->unit_id);
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
}
