#include "psx/types.h"

extern s32 main_pass_fail_roll(s32, s32, void*);
extern u8* D_8018F4E0;

s32 battle_teleport_chances(void) {
    u8* ctx = D_8018F4E0;
    s32 dx, dy;

    if (ctx[0x24] & 4) {
        return 1;
    }
    dy = ctx[0xA] - ctx[7];
    dx = ctx[0xB] - ctx[8];
    if (dy < 0)
        dy = -dy;
    if (dx < 0)
        dx = -dx;
    return main_pass_fail_roll(0x64, ((dy + dx) - ctx[6]) * 10, ctx);
}

/* padding */
