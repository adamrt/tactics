#include "psx/types.h"

extern s32 func_80181F38(s32, s32, s32, s32);

s32 battle_math_skill_ability_display(s32 arg0, s32 arg1, s32 arg2) {
    return func_80181F38(arg0, arg1 & 0xFF, arg2, 0xF0);
}
