#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern void battle_disable_acting_statuses(battle_stats_t* unit);

s32 battle_remove_charging_status_ability_ct(battle_stats_t* unit, s32 do_disable) {
    u8 mount_info;

loop:
    if ((unit->current_status[0] & 8) && unit->charged_ability_ct != 0xFF && unit->last_skillset_id == 8) {
        if (do_disable != 0) {
            battle_disable_acting_statuses(unit);
            return 1;
        }
        return 1;
    }
    mount_info = unit->mount_info;
    if (mount_info & 0x40) {
        unit = &battle_stats[mount_info & 0x1F];
        goto loop;
    }
    return 0;
}
