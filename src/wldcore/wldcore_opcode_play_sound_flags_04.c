#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern void main_play_sound_find_channel(s32 sound_id);

void wldcore_opcode_play_sound_flags_04(void) {
    main_play_sound_find_channel(g_wldcore_opcode_operand_byte);
    g_wldcore_state_flags |= 4;
}
