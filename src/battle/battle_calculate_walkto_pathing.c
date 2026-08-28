#include "psx/types.h"

extern void func_8017813C(s32, s32, s32, s32, s32, s32, s32, s32, s32, void*, s32);

void battle_calculate_walkto_pathing(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h) {
    s32 sp30;
    func_8017813C(a, b, c, d, e, f, g, h, 1, &sp30, 0);
}
