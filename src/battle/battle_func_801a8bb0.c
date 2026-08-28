#include "psx/types.h"

extern void func_801A8A6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void battle_func_801a8bb0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_801A8A6C(arg0, arg1, (arg3 << 13) / arg2, arg4);
}
