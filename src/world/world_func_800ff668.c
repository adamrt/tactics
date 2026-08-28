#include "psx/types.h"

extern void func_800FF690(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f);

void world_func_800ff668(s32 a, s32 b, s32 c, s32 d, s32 e) {
    func_800FF690(a, b, c, d, e, 0);
}
