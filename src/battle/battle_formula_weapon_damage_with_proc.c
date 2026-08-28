extern int calculate_physical_evade(void);
extern int calculate_weapon_damage(void);
extern void store_reaction_proc_id_and_target(void);

void battle_formula_weapon_damage_with_proc(void) {
    if (calculate_physical_evade() == 0) {
        if (calculate_weapon_damage() == 0) {
            store_reaction_proc_id_and_target();
        }
    }
}
