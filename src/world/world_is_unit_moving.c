#include "psx/types.h"

extern s32 battle_does_misc_unit_id_exist(s32 id);
extern s32 battle_unit_moving_check_by_misc_id(s32 id);

/* Return whether one unit, or any existing unit when id is -1, is moving. */
s32 world_is_unit_moving(s32 id) {
    s32 i;

    if (id != -1) {
        if (battle_unit_moving_check_by_misc_id(id) == 0) {
            goto return_zero;
        }
        goto battle_return_one;
    }
    for (i = 0; i < 21; i += 1) {
        if (battle_does_misc_unit_id_exist(i) != 0 && battle_unit_moving_check_by_misc_id(i) != 0) {
            return 1;
        }
    }
return_zero:
    return 0;
battle_return_one:
    return 1;
}
