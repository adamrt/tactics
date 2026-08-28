#include "psx/types.h"

extern s32* g_proposition_data_base;

void* wldcore_get_proposition_data_pointer(s32 proposition_index) {
    s32* table = g_proposition_data_base;

    return (u8*)table + table[proposition_index];
}
