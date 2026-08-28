#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;
extern s32 g_casting_unit_misc_id;

battle_misc_data_t* battle_get_misc_data_at_map_coords_3(s32 map_x, s32 map_y, s32 map_z) {
    battle_misc_data_t* matches[16];
    battle_misc_data_t* unit;
    s32 count;
    s32 index;

    count = 0;
    unit = g_misc_unit_list_head;
    while (unit != 0) {
        if ((unit->map_x == map_x) && (unit->map_y == map_y) && (unit->map_z == map_z) && (unit->battle_data != 0) && (unit->battle_data->entd_slot != 0xFF) && ((unit->status_flags_5_6 & 9) != 0)) {
            matches[count++] = unit;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    if (count == 0) {
        goto return_null;
    }
    for (index = 0; index < count; index++) {
        if (matches[index]->unit_id == g_casting_unit_misc_id) {
            return matches[index];
        }
    }
    return matches[0];
return_null:
    return 0;
}
