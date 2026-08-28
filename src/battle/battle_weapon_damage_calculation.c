#include "psx/types.h"

extern void func_80185A9C(void);
extern void battle_apply_charge(void);
extern void battle_apply_weapon_element_strengthen(void);
extern void battle_calculate_physical_damage(void);
extern void battle_elemental_damage_modification(void);
extern void battle_elemental_absorption(void);
extern s32 func_801884C0(void);
extern u8* g_target_current_action;

s32 battle_weapon_damage_calculation(void) {
    func_80185A9C();
    battle_apply_charge();
    battle_apply_weapon_element_strengthen();
    battle_calculate_physical_damage();
    battle_elemental_damage_modification();
    if (*g_target_current_action == 0)
        return 1;
    battle_elemental_absorption();
    return func_801884C0();
}
