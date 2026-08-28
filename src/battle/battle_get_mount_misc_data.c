#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);

battle_misc_data_t* battle_get_mount_misc_data(battle_misc_data_t* unit) {
    if (unit->mount_rider_value == 1) {
        return battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
    }
    return unit;
}
