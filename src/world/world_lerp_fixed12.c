#include "psx/types.h"

s32 world_lerp_fixed12(s32 from, s32 to, s32 t) {
    return ((to - from) * t) / 4096 + from;
}
