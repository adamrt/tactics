#include "psx/types.h"

extern u16 g_wldcore_state_flags;

void wldcore_or_flags_8008b38c_mask_04(void) {
    u16* flags;

    flags = &g_wldcore_state_flags;
    *flags |= 0x04;
}
