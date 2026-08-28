#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);
extern void battle_update_display_by_misc_id(u32 misc_id);

void battle_update_anim_display_for_all_targets(battle_misc_data_t* unit) {
    s32 counter;
    battle_misc_data_t* target;

    if (unit->target_count != 0) {
        for (counter = 0; counter < unit->target_count; counter++) {
            target = battle_get_unit_misc_data_by_battle_id(unit->target_list[counter]);
            if (target != 0) {
                battle_update_display_by_misc_id(target->unit_id);
            }
        }
    }
}
