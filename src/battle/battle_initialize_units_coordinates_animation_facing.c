#include "fft/battle.h"
#include "psx/types.h"

extern void battle_store_unit_animation_facing(u32 animation, s16 facing, battle_misc_data_t* unit);

void battle_initialize_units_coordinates_animation_facing(battle_misc_data_t* unit) {
    unit->centre_tile_offset = 0x3C;
    battle_store_unit_animation_facing(0x3C, unit->facing, unit);
    if (unit->movement_path_count == 0xFE) {
        unit->movement.bytes.destination_x = unit->movement_path[0];
        unit->movement.bytes.destination_y = unit->movement_path[1];
        unit->movement.bytes.destination_z = unit->movement_path[2];
    } else {
        unit->movement.bytes.destination_x = unit->map_x;
        unit->movement.bytes.destination_y = unit->map_y;
        unit->movement.bytes.destination_z = unit->map_z;
    }
}
