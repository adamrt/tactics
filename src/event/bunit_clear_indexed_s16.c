#include "psx/types.h"

extern s16 g_bunit_indexed_values[];

void bunit_clear_indexed_s16(void) {
    s32 index;

    for (index = 15; index >= 0; index--) {
        g_bunit_indexed_values[index] = 0;
    }
}
