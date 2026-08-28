#include "psx/types.h"

extern u8 g_current_ability[];
extern void battle_apply_charge(void);
extern void battle_calculate_physical_damage(void);

void battle_formula_gun_damage(void) {
    u16 weapon_power = g_current_ability[0x42];

    *(u16*)(g_current_ability + 0x0e) = weapon_power;
    *(u16*)(g_current_ability + 0x10) = weapon_power;
    battle_apply_charge();
    battle_calculate_physical_damage();
}
