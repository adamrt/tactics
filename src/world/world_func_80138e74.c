#include "psx/types.h"

extern s16 D_8019520C;

s32 world_func_80138e74(void) {
    s16 mode = D_8019520C;

    if (mode == 0) {
        return 0x5DC;
    }
    return (mode == 1) ? 0x578 : 0;
}
