#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void rider_mounts_unit(battle_misc_data_t* rider, battle_misc_data_t* mount);

s32 battle_mount_by_misc_ids(u32 rider_misc_id, u32 mount_misc_id) {
    battle_misc_data_t* rider;
    battle_misc_data_t* mount;

    rider = battle_get_unit_misc_data_by_misc_id(rider_misc_id & 0xffff);
    mount = battle_get_unit_misc_data_by_misc_id(mount_misc_id & 0xffff);
    if ((rider != 0) && (mount != 0)) {
        rider_mounts_unit(rider, mount);
        return 1;
    }
    return 0;
}
