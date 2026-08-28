#include "psx/types.h"

extern void* g_effect_file_ptrs[];

void* battle_get_effect_file_pointer(s16 effect_id) {
    return g_effect_file_ptrs[effect_id];
}
