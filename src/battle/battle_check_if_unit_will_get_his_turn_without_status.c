#include "psx/types.h"

extern s32 battle_calculate_clockticks_until_unit_acts(s32);

s32 battle_check_if_unit_will_get_his_turn_without_status(s32 arg0, s32 arg1) {
    if (arg1 == 0x22 || (u32)(arg1 - 0x24) < 2U) {
        if (battle_calculate_clockticks_until_unit_acts(arg0) > *(u8*)(arg0 + arg1 + 0x45)) {
            return 0;
        }
    }
    return 1;
}
