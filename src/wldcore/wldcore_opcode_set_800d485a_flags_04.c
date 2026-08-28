#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern s16 D_800D485A;
extern s32 DrawSync(s32 mode);
extern void func_80068B3C(s32 arg0);
extern void func_800686C8(void);

void wldcore_opcode_set_800d485a_flags_04(void) {
    s32 value;

    value = g_wldcore_opcode_operand_byte;
    if (D_800D485A != value) {
        DrawSync(0);
        D_800D485A = value;
        func_80068B3C(value);
        func_800686C8();
    }
    g_wldcore_state_flags |= 4;
}
