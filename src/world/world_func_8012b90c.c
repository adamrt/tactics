#include "psx/types.h"

extern s16 D_801CA73C[16];

void world_func_8012b90c(void) {
    s32 i;

    for (i = 15; i >= 0; i--) {
        D_801CA73C[i] = 0;
    }
}
