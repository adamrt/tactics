#include "psx/types.h"

extern s16 D_801660EC;
extern s16 D_801660EE;
extern s16 D_801660F0;
extern s16 D_801660F2;

void battle_func_8014a6a4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_801660EC = arg0;
    D_801660EE = arg1;
    D_801660F0 = arg2;
    D_801660F2 = arg3;
}
