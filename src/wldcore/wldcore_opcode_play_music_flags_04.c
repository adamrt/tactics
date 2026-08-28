#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern void func_8008c150(s32 music_id);

void wldcore_opcode_play_music_flags_04(void) {
    func_8008c150(g_wldcore_opcode_operand_byte);
    g_wldcore_state_flags |= 4;
}
