#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern u16 D_800D486C;

void wldcore_opcode_set_800d486c_flags_04(void) {
    u16 flags;

    flags = g_wldcore_state_flags | 4;
    D_800D486C = g_wldcore_opcode_operand_byte;
    g_wldcore_state_flags = flags;
}
