#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(s32 misc_id);
extern void battle_update_display_by_misc_id(s32 unit_id);
extern void battle_move_to_previous_map_square(battle_misc_data_t* unit);

void battle_undo_mount(battle_misc_data_t* unit) {
    battle_misc_data_t* other;

    if (unit->mount_rider_value == 1) {
        other = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        other->mount_rider_value = 0;
        battle_update_display_by_misc_id(other->unit_id);
    }
    battle_move_to_previous_map_square(unit);
    if (unit->mount_rider_value == 2) {
        other = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (other != 0) {
            battle_move_to_previous_map_square(other);
            battle_update_display_by_misc_id(other->unit_id);
        }
    } else if (unit->mount_rider_value == 1) {
        unit->status_flags_1_4 |= 2;
        other = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (other != 0) {
            other->mount_rider_value = 2;
            other->mount_rider_id = unit->unit_id;
            battle_update_display_by_misc_id(other->unit_id);
        }
    } else {
        unit->status_flags_1_4 &= ~2;
    }
    battle_update_display_by_misc_id(unit->unit_id);
}
