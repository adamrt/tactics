#include "psx/types.h"

extern u8 D_801937D3;

void battle_null_some_tile_data(void) {
    s32 i;
    u8* p;

    i = 0x1FF;
    p = &D_801937D3;
    do {
        p[1] = 0;
        i -= 1;
        p -= 5;
    } while (i >= 0);
}
