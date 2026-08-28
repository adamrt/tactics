#include "psx/types.h"

extern u32 D_8016E478;
extern u32 D_8016E47C;

void world_func_80106374(u32 arg0, u32 arg1) {
    D_8016E478 = arg0 + 0xA000;
    D_8016E47C = arg1;
}
