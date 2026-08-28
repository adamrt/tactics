#include "psx/types.h"

extern u8 g_current_ability[];
extern void decide_magic_gun_ability(void);
extern void battle_apply_charge(void);
extern void battle_apply_weapon_element_strengthen(void);
extern void battle_apply_magical_support_status_compatibility(void);
extern int battle_calculate_elemental_xa_times_ya(void);
extern void apply_faith_to_action_damage(void);
extern void apply_elemental_absorption(void);

void battle_formula_magic_gun(void) {
    u16 weapon_power;
    u16 ability_y;

    decide_magic_gun_ability();
    weapon_power = g_current_ability[0x42];
    ability_y = g_current_ability[0x3a];
    *(u16*)(g_current_ability + 0x0e) = weapon_power;
    *(u16*)(g_current_ability + 0x10) = ability_y;
    battle_apply_charge();
    battle_apply_weapon_element_strengthen();
    battle_apply_magical_support_status_compatibility();
    if (battle_calculate_elemental_xa_times_ya() == 0) {
        apply_faith_to_action_damage();
        apply_elemental_absorption();
    }
}
