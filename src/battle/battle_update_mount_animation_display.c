#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);
extern void set_rider_mount_map_position(u8 misc_id, u8 map_x, u8 map_y,
    u8 map_z, u8 facing_index);

void battle_update_mount_animation_display(battle_misc_data_t* unit) {
    battle_misc_data_t* mounted_unit;

    set_rider_mount_map_position(
        unit->battle_data->misc_unit_id, unit->map_x, unit->map_y, unit->map_z,
        (u8)(*(s16*)&unit->facing / 0x400));

    if (unit->mount_rider_value != 0) {
        mounted_unit = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (mounted_unit != 0) {
            mounted_unit->facing = unit->facing;
            /* 0x6c/0x6e: undocumented facing halfwords (wiki page 00009560
             * has no entry); see battle_get_alternate_facing_quadrant_*. */
            *(u16*)((u8*)mounted_unit + 0x6c) = *(u16*)((u8*)unit + 0x6c);
            *(u16*)((u8*)mounted_unit + 0x6e) = *(u16*)((u8*)unit + 0x6e);

            set_rider_mount_map_position(
                mounted_unit->battle_data->misc_unit_id,
                unit->map_x, unit->map_y, unit->map_z,
                (u8)(*(s16*)&unit->facing / 0x400));
        }
    }
}
