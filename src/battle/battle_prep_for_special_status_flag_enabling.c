#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern void special_status_flag_enabling(s32 arg0, s32 arg1, s32 arg2);

s32 battle_prep_for_special_status_flag_enabling(s32 unit_id) {
    battle_stats_t* unit;
    s32 i;

    unit = &battle_stats[unit_id];
    if (unit->entd_slot == 0xFF) {
        return -1;
    }
    i = 0;
    do {
        s32 byte_index = i / 8;
        s32 bit_shift = i & 7;
        if (unit->current_status[byte_index] & (0x80 >> bit_shift)) {
            special_status_flag_enabling(i + 1, 1, unit_id);
        }
        i += 1;
    } while (i < 0x28);
    return 0;
}
