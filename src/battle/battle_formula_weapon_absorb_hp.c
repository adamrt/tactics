extern int calculate_physical_evade(void);
extern void calculate_base_xa(void);
extern void battle_apply_charge(void);
extern void battle_calculate_physical_damage(void);
extern void apply_hp_absorption(void);

void battle_formula_weapon_absorb_hp(void) {
    if (calculate_physical_evade() == 0) {
        calculate_base_xa();
        battle_apply_charge();
        battle_calculate_physical_damage();
        apply_hp_absorption();
    }
}
