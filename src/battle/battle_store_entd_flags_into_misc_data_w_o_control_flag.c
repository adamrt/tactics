#include "fft/battle.h"
#include "psx/types.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8);

/* Copy the ENTD control-byte into the unit's misc data, but strip the
   0x08 (player-controllable) bit when the unit's stats mark it as
   AI-only. Also propagates to the linked mount unit, if any. */
void battle_store_entd_flags_into_misc_data_w_o_control_flag(battle_misc_data_t* unit) {
    u8 entd_flags;
    u8 mount_entd_flags;
    battle_misc_data_t* mount;

    entd_flags = unit->battle_data->team_flags;
    unit->team_flags = entd_flags;
    if (unit->battle_data->auto_battle_setting != 0) {
        unit->team_flags = entd_flags & 0xF7;
    }
    if (unit->mount_rider_value != 0) {
        mount = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        mount_entd_flags = mount->battle_data->team_flags;
        mount->team_flags = mount_entd_flags;
        if (mount->battle_data->auto_battle_setting != 0) {
            mount->team_flags = mount_entd_flags & 0xF7;
        }
    }
}
