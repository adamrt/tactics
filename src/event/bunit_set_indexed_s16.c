#include "psx/types.h"

extern s16 g_bunit_indexed_values[];

s32 bunit_set_indexed_s16(u8 index, s16 value) {
    return g_bunit_indexed_values[index] = value;
}
