#include "psx/types.h"

extern void func_8014C18C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

void battle_func_8014c164(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_8014C18C(arg0, arg1, arg2, arg3, arg4, 0);
}
