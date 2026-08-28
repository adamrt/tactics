#include "fft/battle.h"

extern void battle_set_move_and_screen_coords(battle_misc_data_t* unit);
extern void set_rider_mount_map_position(u8 misc_id, u8 map_x, u8 map_y,
    u8 map_z, u8 facing_index);
extern void battle_store_unit_animation_facing_movement_data(u32 animation, s16 facing,
    u8* unit);

void battle_move_to_previous_map_square(battle_misc_data_t* unit) {
    unit->map_x = unit->previous_map_x;
    unit->map_y = unit->previous_map_y;
    unit->map_z = unit->previous_map_z;
    unit->facing = unit->previous_facing;
    unit->mount_rider_value = unit->previous_mount_rider_value;
    unit->mount_rider_id = unit->previous_mount_rider_id;
    unit->current_unit_id_plus_one = unit->previous_unit_id_plus_one;
    battle_set_move_and_screen_coords(unit);
    set_rider_mount_map_position(unit->battle_data->misc_unit_id,
        unit->map_x, unit->map_y, unit->map_z,
        (u8)(*(s16*)&unit->facing / 0x400));
    battle_store_unit_animation_facing_movement_data(
        (u32)unit->encoded_animation >> 1,
        *(s16*)&unit->facing,
        (u8*)unit);
}
