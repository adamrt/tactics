#include "psx/types.h"

extern u8* g_battle_data;

u32 main_get_otag(void) {
    return *(u32*)(g_battle_data + 0xe5b4);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
