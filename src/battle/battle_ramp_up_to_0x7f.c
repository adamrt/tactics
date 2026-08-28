#include "psx/types.h"

s32 battle_ramp_up_to_0x7f(s32 x) {
    if (x == 0) {
        return 0;
    }
    if (x >= 0x60) {
        x = 0x7F;
    } else {
        x = (x * 0x7F) / 96;
    }
    return x;
}
