#include "psx/types.h"

extern u8 D_801B8BA4[];

s32 battle_func_801adae0(u8 index) {
    return *(s32*)&D_801B8BA4[index * 0x54];
}
