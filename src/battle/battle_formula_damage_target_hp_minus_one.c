extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy_no_elemental(void);
extern void calculate_target_hp_minus_one_damage(void);

void battle_formula_damage_target_hp_minus_one(void) {
    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy_no_elemental() == 0) {
            calculate_target_hp_minus_one_damage();
        }
    }
}
