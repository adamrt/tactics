#include "fft/battle.h"

extern void func_800687E0(battle_misc_data_t* unit, u8* buf);
extern void func_801ADFEC(u8 elem, u8* buf, s32 arg2);
extern u8 D_80063ABE;

void battle_set_evade_type_data_and_weapon_element_effect(battle_misc_data_t* unit, s32 arg1) {
    u8 buf[0xc8];
    func_800687E0(unit, buf);
    func_801ADFEC((&D_80063ABE)[unit->used_item_or_weapon_id * 8], buf, arg1);
}
