#include "psx/types.h"

extern void battle_set_move_act_flags(s32, s32, s32);

void battle_set_only_action_taken(s32 arg0) {
    battle_set_move_act_flags(arg0, 0, 1);
}
