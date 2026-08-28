#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u32 g_system_flags;

void wldcore_opcode_system_flag_800_flags_04(void) {
    u16* flags;
    u32 sys;
    u16 value;

    flags = &g_wldcore_state_flags;
    sys = g_system_flags;
    value = *flags;
    g_system_flags = sys | 0x800;
    *flags = (value & 0xFF7F) | 4;
}
