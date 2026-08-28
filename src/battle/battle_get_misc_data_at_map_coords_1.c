#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;

battle_misc_data_t* battle_get_misc_data_at_map_coords_1(s32 map_x, s32 map_y, s32 map_z) {
    battle_misc_data_t* unit;

    unit = g_misc_unit_list_head;
    while (unit != 0) {
        if (unit->map_x == map_x && unit->map_y == map_y && unit->map_z == map_z) {
            return unit;
        }
        unit = (battle_misc_data_t*)unit->previous;
    }
    return 0;
}
