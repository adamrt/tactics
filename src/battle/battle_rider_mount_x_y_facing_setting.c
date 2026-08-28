#include "fft/battle.h"
#include "psx/types.h"

extern void func_8017FDDC(u8, u8, u8, u8, u8);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8);

void battle_rider_mount_x_y_facing_setting(battle_misc_data_t* unit) {
    battle_misc_data_t* mount;
    s16 rot;
    s32 unused[4];

    if (unit != 0) {
        if ((unit->status_flags_1_4 & 4) == 0) {
            /* The facing halfwords are read signed (lh) here. */
            rot = *(s16*)&unit->attack_facing;
            if (rot != -1) {
                unit->facing = rot;
                func_8017FDDC(unit->battle_data->misc_unit_id, unit->map_x,
                    unit->map_y, unit->map_z, rot / 1024);
                /* Stored as a signed halfword (li -1, not ori 0xffff). */
                *(s16*)&unit->attack_facing = -1;
                if (unit->mount_rider_value != 0) {
                    mount = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
                    mount->facing = unit->facing;
                    func_8017FDDC(unit->battle_data->misc_unit_id, unit->map_x,
                        unit->map_y, unit->map_z,
                        *(s16*)&unit->facing / 1024);
                }
            }
        } else {
            *(s16*)&unit->attack_facing = -1;
        }
    }
}
