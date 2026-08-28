#include "psx/types.h"

extern void battle_charge_skillset_loading(s32 a0, s32 a1, s32 a2, s32* sp18, s32* sp28);

void battle_call_charge_skillset_loading(s32 a0, s32 a1, s32 a2) {
    s32 sp18[4];
    s32 sp28[4];
    battle_charge_skillset_loading(a0, (u8)a1, a2, sp18, sp28);
}
