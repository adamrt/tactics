#include "psx/types.h"

extern s16 D_801CA73C[];

s16 world_func_8012b950(u8 index, s16 value) {
    D_801CA73C[index] = value;
    return value;
}
