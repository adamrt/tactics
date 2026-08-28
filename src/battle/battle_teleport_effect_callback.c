#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void battle_set_secondary_effect_teleport(battle_misc_data_t* unit);

s32 battle_teleport_effect_callback(u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        battle_set_secondary_effect_teleport(unit);
        return 1;
    }
    return 0;
}
