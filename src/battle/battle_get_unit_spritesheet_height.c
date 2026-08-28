#include "fft/battle.h"

extern u8 g_spritesheet_data[];

u32 battle_get_unit_spritesheet_height(battle_misc_data_t* unit) {
    if (unit == 0) {
        return 0;
    }
    if ((unit->status_flags_5_6 & 9) != 0) {
        return 0;
    }
    if ((unit->status_flags_1_4 & 4) != 0) {
        return 0;
    }
    return g_spritesheet_data[unit->spritesheet_id * 4 + 3];
}
