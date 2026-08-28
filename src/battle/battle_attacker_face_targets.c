#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u8 battle_id);
extern void battle_rider_mount_x_y_facing_setting(battle_misc_data_t* target);

/* For each live target in the attacker's target list, tell it to face the
   attacker. */
void battle_attacker_face_targets(battle_misc_data_t* unit) {
    s32 i;
    battle_misc_data_t* target;

    if (unit->target_count != 0) {
        i = 0;
        while (i < (s32)unit->target_count) {
            target = battle_get_unit_misc_data_by_battle_id(unit->target_list[i]);
            if (target != 0) {
                battle_rider_mount_x_y_facing_setting(target);
            }
            i++;
        }
    }
}
