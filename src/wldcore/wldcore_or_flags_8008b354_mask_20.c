#include "psx/types.h"

extern u16 g_wldcore_state_flags;

void wldcore_or_flags_8008b354_mask_20(void) {
    u16* flags;

    flags = &g_wldcore_state_flags;
    *flags |= 0x20;
}
