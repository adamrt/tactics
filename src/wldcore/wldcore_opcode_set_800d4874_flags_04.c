#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u32 g_wldcore_opcode_instruction;
extern u32 D_800D4874;

void wldcore_opcode_set_800d4874_flags_04(void) {
    u32 word;
    u16 flags;

    word = g_wldcore_opcode_instruction;
    flags = g_wldcore_state_flags;
    D_800D4874 = (word << 8) >> 16;
    g_wldcore_state_flags = flags | 4;
}
