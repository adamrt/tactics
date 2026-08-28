#include "psx/types.h"

extern s16 battle_load_halfword(void);
extern s32 func_80133158(s16 x);
extern void battle_set_horizontal_flip_flag(s32 x);
extern void battle_unset_horizontal_flip_flag(s32 x);

void battle_mirrorsprite_event_instruction(u8* arg0) {
    s16 hw;
    s32 mode;
    s32 r;

    hw = battle_load_halfword();
    mode = arg0[2];
    r = func_80133158(hw);
    if (r != 0x7D0) {
        if (mode == 1) {
            battle_set_horizontal_flip_flag(r);
        } else {
            battle_unset_horizontal_flip_flag(r);
        }
    }
}
