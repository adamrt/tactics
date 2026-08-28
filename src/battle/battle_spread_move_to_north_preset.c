#include "psx/types.h"

typedef struct {
    u8 pad00[0x3A];
    s16 field_3A; /* 0x3A */
    s16 field_3C; /* 0x3C */
    u8 pad3E[0x44 - 0x3E];
    u8 field_44; /* 0x44 */
    u8 field_45; /* 0x45 */
} SpreadMoveTarget;

extern SpreadMoveTarget* g_battle_scratch_pad_ptr;

void battle_spread_move_to_north_preset(void) {
    SpreadMoveTarget* t = g_battle_scratch_pad_ptr;
    t->field_3C = 1;
    t->field_44 = 6;
    t->field_3A = 0;
    t->field_45 = 4;
}
