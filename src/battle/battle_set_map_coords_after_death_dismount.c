#include "fft/battle.h"

extern void battle_rider_dismount_and_update_display(void);
extern void battle_set_move_and_screen_coords(void* unit);
extern void set_rider_mount_map_position(u8 battle_id, u8 x, u8 y, u8 z,
    u8 elevation);

void battle_set_map_coords_after_death_dismount(battle_misc_data_t* unit) {
    /* pending_attack_result is the "Death by Dismount" word (wiki). */
    if (unit->pending_attack_result != 0) {
        battle_rider_dismount_and_update_display();
        unit->map_x = unit->dismount_x;
        unit->map_y = unit->dismount_y;
        unit->map_z = unit->dismount_z;
        battle_set_move_and_screen_coords(unit);
        set_rider_mount_map_position(
            unit->battle_data->misc_unit_id,
            unit->map_x, unit->map_y, unit->map_z,
            (u8)(*(s16*)&unit->facing / 0x400));
        unit->pending_attack_result = 0;
    }
}
