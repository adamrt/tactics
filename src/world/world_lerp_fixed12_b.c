#include "psx/types.h"

s32 world_lerp_fixed12_b(s32 from, s32 to, s32 t) {
    return ((to - from) * t) / 4096 + from;
}
