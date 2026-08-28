#include "psx/types.h"

extern void func_801817C0(s32 a0, u8 a1, s32 a2, void* sp20, s32 a3, s32 zero, void* sp30, s32 a4);

void battle_charge_skillset_loading(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4) {
    s32 sp20[4];
    s32 sp30[4];
    func_801817C0(a0, (u8)a1, a2, sp20, a3, 0, sp30, a4);
}
