extern void calculate_base_xa(void);
extern void apply_compatibility(void);
extern void battle_apply_charge(void);
extern void apply_physical_xa_modifiers(void);
extern void battle_store_xa_times_ya_damage(void);
extern void apply_undead_reversal(void);

void battle_formula_weapon_heal(void) {
    calculate_base_xa();
    apply_compatibility();
    battle_apply_charge();
    apply_physical_xa_modifiers();
    battle_store_xa_times_ya_damage();
    apply_undead_reversal();
}
