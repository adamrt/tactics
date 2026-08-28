#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* g_last_unit_misc_data;
extern void main_pointer_exception_handler(s32 error_code);

s32 battle_get_map_coords_from_misc_id(u32 misc_id, s16* coords) {
    battle_misc_data_t* unit = g_last_unit_misc_data;

    if (unit != 0) {
        do {
            if (unit->unit_id == (misc_id & 0xffff)) {
                coords[0] = unit->map_x;
                coords[2] = unit->map_y;
                coords[1] = unit->map_z;
                return 1;
            }
            unit = (battle_misc_data_t*)unit->previous;
        } while (unit != 0);
    }
    main_pointer_exception_handler(12);
    return 0;
}
