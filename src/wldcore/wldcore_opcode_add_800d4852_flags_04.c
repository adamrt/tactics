#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u32 g_wldcore_opcode_instruction;
extern u16 D_800D4852;

void wldcore_opcode_add_800d4852_flags_04(void) {
    u16* target;
    u32 word;
    u16 flags;

    target = &D_800D4852;
    word = g_wldcore_opcode_instruction;
    flags = g_wldcore_state_flags;
    *target += (word << 8) >> 16;
    g_wldcore_state_flags = flags | 4;
}
