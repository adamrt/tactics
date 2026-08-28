#include "psx/types.h"

extern s16 D_80153340;

void world_increment_80153340_if_one(void) {
    s16 value = D_80153340;

    if (value == 1) {
        D_80153340 = value + 1;
    }
}
