#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;
extern s32 g_casting_unit_misc_id;

enum {
    MISC_STATUS_CRYSTAL = 0x01,
    MISC_STATUS_TREASURE = 0x08,
    MISC_STATUS_JUMPING = 0x40,
    MISC_STATUS_UNTARGETABLE = MISC_STATUS_CRYSTAL | MISC_STATUS_TREASURE | MISC_STATUS_JUMPING,
    MISC_MOUNT_STATE_RIDER = 1,
};

battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32 map_x, s32 map_y, s32 map_z) {
    battle_misc_data_t* matches[16];
    battle_misc_data_t* unit;
    s32 count;
    s32 index;

    count = 0;
    unit = g_misc_unit_list_head;
    while (unit != 0) {
        if ((unit->map_x == map_x) && (unit->map_y == map_y) && (unit->map_z == map_z) && (unit->battle_data != 0) && (unit->battle_data->entd_slot != 0xFF) && ((unit->status_flags_5_6 & MISC_STATUS_UNTARGETABLE) == 0)) {
            matches[count++] = unit;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    if (count == 0) {
        goto return_null;
    }
    if (count == 1) {
        goto return_first;
    }
    for (index = 0; index < count; index++) {
        if (matches[index]->unit_id == g_casting_unit_misc_id) {
            return matches[index];
        }
    }
    for (index = 0; index < count; index++) {
        if (matches[index]->mount_rider_value == MISC_MOUNT_STATE_RIDER) {
            return matches[index];
        }
    }

return_first:
    return matches[0];
return_null:
    return 0;
}
