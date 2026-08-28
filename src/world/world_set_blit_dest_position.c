#include "psx/types.h"

extern s16 D_801c001c;
extern s16 D_801c001e;

void world_set_blit_dest_position(s32 x, s32 y) {
    D_801c001c = x;
    D_801c001e = y;
}
