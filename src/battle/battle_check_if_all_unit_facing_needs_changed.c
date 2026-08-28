#include "psx/types.h"

extern void* battle_get_unit_misc_data_by_misc_id();
extern void battle_rider_mount_x_y_facing_setting(void* unit);

void battle_check_if_all_unit_facing_needs_changed(void) {
    s32 i = 0;
    do {
        void* unit = battle_get_unit_misc_data_by_misc_id(i & 0xFFFF);
        if (unit) {
            battle_rider_mount_x_y_facing_setting(unit);
        }
        i++;
    } while (i < 0x10);
}
