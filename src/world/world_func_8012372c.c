#include "psx/types.h"

extern u16 D_80062EC0[];

s32 world_func_8012372c(s32 index) {
    u32 value = D_80062EC0[(index & 0x3FF) * 6] >> 1;

    if (value == 0) {
        value = 1;
    }
    return value;
}
