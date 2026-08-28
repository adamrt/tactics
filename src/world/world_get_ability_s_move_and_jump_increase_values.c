#include "psx/types.h"

extern void world_clear_some_data_at_r4_and_r5(s16* a, s16* b);

/* Emit the +Move/+Jump stat deltas granted by the Movement-slot ability:
   0x1E6-0x1E8 grant Move +1/+2/+3 into out[0]; 0x1E9-0x1EB grant Jump
   +1/+2/+3 into out[2]. Anything else zeroes both slots. */
void world_get_ability_s_move_and_jump_increase_values(u16 ability, s16* out) {
    s16 zero_buffer[20];

    world_clear_some_data_at_r4_and_r5(zero_buffer, out);
    if ((u16)(ability - 0x1E6) < 3) {
        out[0] = ability - 0x1E5;
    } else {
        out[0] = 0;
    }
    if ((u16)(ability - 0x1E9) < 3) {
        out[2] = ability - 0x1E8;
    } else {
        out[2] = 0;
    }
}
