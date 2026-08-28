#include "fft/battle.h"
#include "psx/types.h"

s32 battle_check_if_status_should_can_be_added(s32 arg0, battle_stats_t* unit, s32 status) {
    s32 byte_off = status / 8;

    if (!(unit->current_status[byte_off] & (0x80 >> (status - byte_off * 8)))) {
        return 0;
    }
    if (status == 5) {
        if (unit->charged_ability_ct < arg0) {
            return 0;
        }
    } else {
        if (status < 0x18) {
            return 1;
        }
        if (unit->innate_status[byte_off] & (0x80 >> (status - byte_off * 8))) {
            return 1;
        }
        if (unit->status_ct[status - 0x18] < arg0) {
            return 0;
        }
    }
    return 1;
}
