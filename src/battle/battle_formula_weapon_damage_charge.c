extern int calculate_physical_evade_charge(void);
extern void calculate_base_xa(void);
extern void battle_apply_charge(void);
extern void battle_calculate_physical_damage(void);
extern int conditional_status_proc_roll(void);
extern void apply_status_to_action(void);

void battle_formula_weapon_damage_charge(void) {
    if (calculate_physical_evade_charge() == 0) {
        calculate_base_xa();
        battle_apply_charge();
        battle_calculate_physical_damage();
        if (conditional_status_proc_roll() == 0) {
            apply_status_to_action();
        }
    }
}
