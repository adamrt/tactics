#include "psx/types.h"

extern s32 g_animation_continue_check;

s32 battle_get_animation_continue_check(void) {
    return g_animation_continue_check;
}
