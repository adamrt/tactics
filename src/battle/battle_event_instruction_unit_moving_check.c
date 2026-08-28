#include "psx/types.h"

s32 battle_does_misc_unit_id_exist(s32);
s32 battle_unit_moving_check_by_misc_id(s32);

/* Event instruction 0x39: is the unit with this misc id moving (any of the
 * 0x15 units when misc id is -1)? */
s32 battle_event_instruction_unit_moving_check(s32 arg0) {
    s32 i;

    if (arg0 != -1) {
        if (battle_unit_moving_check_by_misc_id(arg0) == 0) {
            goto none;
        }
        return 1;
    }
    for (i = 0; i < 0x15; i++) {
        if ((battle_does_misc_unit_id_exist(i) != 0) && (battle_unit_moving_check_by_misc_id(i) != 0)) {
            return 1;
        }
    }
none:
    return 0;
}
