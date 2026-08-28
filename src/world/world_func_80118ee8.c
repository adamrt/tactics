#include "psx/types.h"

s16 world_func_80118ee8(s16 arg0) {
    if (arg0 < 0x4A) {
        return arg0 + 0x13;
    }
    return arg0 - 0x4A;
}
