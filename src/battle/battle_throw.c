#include "psx/types.h"

extern s32 func_80181CDC(s32, s32);

s32 battle_throw(s32 arg0, s32 arg1) {
    return func_80181CDC(arg0, arg1 & 0xFF) & 0xFF;
}
