#include "psx/types.h"

extern s8 D_8018DF7C;

s32 world_get_8018df7c_or_one(void) {
    s32 value = D_8018DF7C;
    if (value == 0) {
        return 1;
    }
    return value;
}
