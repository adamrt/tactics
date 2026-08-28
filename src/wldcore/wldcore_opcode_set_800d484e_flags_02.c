#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern u16 D_800D484E;

void wldcore_opcode_set_800d484e_flags_02(void) {
    u16 flags;

    flags = g_wldcore_state_flags | 2;
    D_800D484E = g_wldcore_opcode_operand_byte;
    g_wldcore_state_flags = flags;
}
