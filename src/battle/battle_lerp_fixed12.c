#include "psx/types.h"

s32 battle_lerp_fixed12(s32 start, s32 end, s32 factor) {
    return ((end - start) * factor) / 4096 + start;
}
