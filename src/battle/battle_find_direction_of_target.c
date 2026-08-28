#include "psx/types.h"

s32 battle_find_direction_of_target(s8* a, s8* b) {
    s32 z1 = a[2];
    s32 x1 = a[0];
    s32 x2 = b[0];
    s32 z2 = b[2];
    s32 d = ((z1 - x1) + x2) - z2;
    s32 e = ((z1 + x1) - x2) - z2;
    s32 v0;

    if (d <= 0) {
        if (e < 0)
            return 0;
        v0 = 0;
    } else {
        if (e <= 0)
            return 1;
        v0 = 1;
    }
    if (d >= 0 && e > 0)
        return 2;
    if (d < 0 && e >= 0)
        return 3;
    return 4;
}
