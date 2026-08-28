extern int calculate_physical_evade(void);
extern int calculate_weapon_damage(void);
extern void apply_status_to_action(void);

void battle_formula_weapon_damage(void) {
    if (calculate_physical_evade() == 0) {
        if (calculate_weapon_damage() == 0) {
            apply_status_to_action();
        }
    }
}
