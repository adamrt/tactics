#include "psx/types.h"

extern u16 g_wldcore_state_flags;
extern u8 g_wldcore_opcode_operand_byte;
extern s32 D_800D4630;
extern u16 D_800D486A;
extern s32 main_set_current_music_target(s32 volume, s32 time);

void wldcore_opcode_fade_out_music_flags_04(void) {
    s32* state;
    s32 operand;

    state = &D_800D4630;
    *state &= ~1;
    operand = g_wldcore_opcode_operand_byte;
    main_set_current_music_target(0, operand * 3);
    g_wldcore_state_flags |= 4;
    D_800D486A &= 0xFF00;
}
