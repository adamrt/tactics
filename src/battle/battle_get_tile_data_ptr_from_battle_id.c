#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);
extern u8* get_tile_data_ptr(u32 x, u32 y, u32 elevation);

u8* battle_get_tile_data_ptr_from_battle_id(u32 battle_id) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_battle_id(battle_id & 0xffff);

    return get_tile_data_ptr(unit->map_x, unit->map_y, unit->map_z);
}
