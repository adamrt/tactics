#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;
extern s32 g_source_unit_misc_id;

battle_misc_data_t* battle_get_source_unit_misc_data(void) {
    battle_misc_data_t* unit;
    s32 source_id;

    unit = g_misc_unit_list_head;
    if (unit != 0) {
        source_id = g_source_unit_misc_id;
        do {
            if (unit->unit_id == source_id) {
                return unit;
            }
            unit = (battle_misc_data_t*)unit->previous;
        } while (unit != 0);
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
