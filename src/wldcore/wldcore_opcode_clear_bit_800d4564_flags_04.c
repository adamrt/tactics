#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern u32 D_800D4564[];
extern void func_800920E8(u32* bits, s32 index, s32 set);

void wldcore_opcode_clear_bit_800d4564_flags_04(void) {
    func_800920E8(D_800D4564, g_wldcore_opcode_operand_byte, 0);
    g_wldcore_state_flags |= 4;
}
