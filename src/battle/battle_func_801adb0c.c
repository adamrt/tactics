#include "psx/types.h"

extern s32 D_801B8BA4[];

void battle_func_801adb0c(u8 arg0) {
    D_801B8BA4[arg0 * 21] = 3;
}
