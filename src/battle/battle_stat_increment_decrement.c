#include "psx/types.h"

s32 battle_stat_increment_decrement(s32 mod, u8* stat, u8 max, u8 min) {
    s32 amount;
    s32 value;

    value = stat[0];
    amount = mod & 0x7F;
    if (max == 0xFF && amount == 0x7F) {
        amount = 0xFF;
    }

    if ((mod & 0x80) != 0) {
        value = value + amount;
    } else {
        value = value - amount;
    }

    if (value < min) {
        value = min;
    }
    if (value > max) {
        value = max;
    }

    if (value == stat[0]) {
        return 0;
    }
    stat[0] = value;

    if (min == 1) {
        value = stat[0] + stat[3];
        if (value > max) {
            value = max;
        }
        stat[6] = value;
    }
    return 1;
}
