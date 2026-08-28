#include "psx/types.h"

extern u8 g_smd_allocator_table[16];

void main_clear_smd_allocator_table(void) {
    int index = 15;
    u8* entry = &g_smd_allocator_table[15];

    for (; index >= 0; index--, entry--) {
        *entry = 0;
    }
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
