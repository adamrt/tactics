#include "psx/types.h"

extern void D_8014B394(void);
extern void (*D_80173CA8)(void);
extern void func_8014CEB4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void battle_func_8014b320(s32 arg0, s32 arg1, s32 arg2) {
    D_80173CA8 = D_8014B394;
    func_8014CEB4(arg0, arg1, arg2, 1);
}
