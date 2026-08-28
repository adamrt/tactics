#include "psx/types.h"

extern s32 battle_check_if_unit_can_react(s32 arg0);
extern s32 battle_reaction_check(s32 arg0);
extern void battle_check_if_unit_can_evade(s32 arg0);

void battle_check_if_unit_can_react_1(s32 arg0) {
    if (battle_check_if_unit_can_react(arg0) == 0 && battle_reaction_check(arg0) == 0) {
        battle_check_if_unit_can_evade(arg0);
    }
}
