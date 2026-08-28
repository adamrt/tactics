#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);

void battle_rider_dismounts(battle_misc_data_t* unit) {
    battle_misc_data_t* mount;
    if (unit->mount_rider_value == 1) {
        mount = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        unit->current_unit_id_plus_one = 0;
        unit->mount_rider_value = 0;
        unit->mount_rider_id = 0;
        unit->status_flags_1_4 = unit->status_flags_1_4 & ~2;
        if (mount != 0) {
            mount->mount_rider_value = 0;
            mount->mount_rider_id = 0;
        }
    }
}
