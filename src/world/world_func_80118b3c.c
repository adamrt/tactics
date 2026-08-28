#include "psx/types.h"

extern u8 D_801C8364[];
extern void* memset(void* dst, s32 c, s32 n);

void world_func_80118b3c(void) {
    memset(D_801C8364, 0, 0x54);
}
