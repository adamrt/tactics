#include "psx/types.h"

extern s16 D_8016605C;

void battle_increment_8016605c_if_one(void) {
    s32 unused;

    if (D_8016605C == 1) {
        D_8016605C = D_8016605C + 1;
    }
}
