#include "psx/types.h"

extern s32 func_8019693C(s32 arg0, s32 arg1);

void battle_get_positive_priority(s32 arg0) {
    if (func_8019693C(arg0, 0) == 0) {
        func_8019693C(0x7FFFFFFF, 1);
    }
}
