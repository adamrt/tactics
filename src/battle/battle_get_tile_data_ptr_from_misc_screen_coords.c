#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern u8* battle_get_tile_data_pointer(s32 x, s32 y, s32 elevation);

u8* battle_get_tile_data_ptr_from_misc_screen_coords(u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    return battle_get_tile_data_pointer(unit->screen_x / 28, unit->screen_y / 28,
        unit->map_z);
}
