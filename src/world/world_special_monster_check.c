#include "psx/types.h"

s32 world_special_monster_check(s32 arg0) {
    s32 result;

    result = (u32)(arg0 - 0x3C) < 0xEU;
    if ((u32)(arg0 - 0x90) < 0xBU) {
        result = 1;
    }
    return result;
}
