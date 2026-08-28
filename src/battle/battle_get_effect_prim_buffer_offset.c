#include "psx/types.h"

extern s32 g_effect_prim_buffer_offset;

s32 battle_get_effect_prim_buffer_offset(void) {
    return g_effect_prim_buffer_offset;
}
