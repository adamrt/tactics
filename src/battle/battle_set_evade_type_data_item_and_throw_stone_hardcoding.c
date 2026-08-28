#include "fft/battle.h"

extern void func_800687E0(battle_misc_data_t* arg0, u8* sp);
extern void func_801ADE7C(u8 t, u8* sp);
extern u8 D_800943C4;

/* Pick the evade-animation type: ability 0x94 (Throw Stone) is hardcoded to
   type 6, abilities 0x170-0x189 and 0x17E share the item-toss branch (0x10),
   and everything else looks the type up in the per-weapon evade table. */
void battle_set_evade_type_data_item_and_throw_stone_hardcoding(battle_misc_data_t* unit) {
    u8 scratch[0xC8];
    u16 ability_id;
    u8 evade_type;
    func_800687E0(unit, scratch);
    ability_id = unit->used_ability_id;
    if (ability_id == 0x94) {
        evade_type = 6;
    } else {
        evade_type = 0x10;
        if ((ability_id != 0x17E) && ((u32)(unit->used_ability_id - 0x170) >= 0x1AU)) {
            evade_type = (&D_800943C4)[unit->equipped_weapon_type];
        }
    }
    func_801ADE7C(evade_type, scratch);
}
