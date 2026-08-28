#include "psx/types.h"

extern s32 g_effect_gravity_modifier;

s32 battle_func_801af3a4(s32 arg0) {
    s32 value;

    arg0 >>= 6;
    value = g_effect_gravity_modifier;
    return value / 2 - (arg0 * arg0) / (value >> 11);
}
