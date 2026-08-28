#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

s32 battle_set_shadow_graphic_trigger_by_misc_id(u32 misc_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit != 0) {
        unit->shadow_graphic_trigger = 1;
        return 1;
    }
    return 0;
}
