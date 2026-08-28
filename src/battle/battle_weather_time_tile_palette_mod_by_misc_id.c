#include "psx/types.h"

extern u8* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void weather_time_tile_palette_mod(u8* unit, u32 arg1, u32 arg2);

void battle_weather_time_tile_palette_mod_by_misc_id(u32 misc_id) {
    u8* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);

    if (unit != 0) {
        weather_time_tile_palette_mod(unit, 0, 1);
    }
}
