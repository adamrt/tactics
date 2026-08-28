#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern u8 D_800D484A;
extern u8 D_800D484B;
extern u16 D_800D484E;
extern s32 rand(void);

void wldcore_opcode_set_800d484e_random_operand_flags_02(void) {
    s32 pick;
    s32 value;

    pick = (rand() * 3) >> 15;
    if (pick == 0) {
        value = g_wldcore_opcode_operand_byte;
    }
    if (pick == 1) {
        value = D_800D484A;
    }
    if (pick == 2) {
        value = D_800D484B;
    }
    D_800D484E = value;
    g_wldcore_state_flags |= 2;
}
