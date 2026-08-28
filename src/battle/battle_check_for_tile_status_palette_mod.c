#include "fft/battle.h"

extern void func_800822BC(battle_misc_data_t* unit, s32 arg1, s32 arg2);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);

void battle_check_for_tile_status_palette_mod(battle_misc_data_t* unit, s32 arg1, s32 arg2) {
    battle_misc_data_t* other;

    if (!(unit->movement.word & 0x04000000)) {
        func_800822BC(unit, arg1, arg2);
    }
    if (unit->mount_rider_value != 0) {
        other = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (other != 0 && !(other->movement.word & 0x04000000)) {
            func_800822BC(other, arg1, arg2);
        }
    }
}
