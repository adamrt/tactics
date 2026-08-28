#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);
extern void battle_update_display_by_misc_id(u8 arg0);

void battle_rider_dismount_and_update_display(battle_misc_data_t* rider) {
    battle_misc_data_t* mount;

    if (rider->mount_rider_value == 1) {
        mount = battle_get_unit_misc_data_by_misc_id(rider->mount_rider_id);
        rider->current_unit_id_plus_one = 0;
        rider->mount_rider_value = 0;
        rider->mount_rider_id = 0;
        rider->status_flags_1_4 &= -3;
        battle_update_display_by_misc_id(rider->unit_id);
        if (mount != 0) {
            mount->mount_rider_value = 0;
            mount->mount_rider_id = 0;
            battle_update_display_by_misc_id(mount->unit_id);
        }
    }
}
