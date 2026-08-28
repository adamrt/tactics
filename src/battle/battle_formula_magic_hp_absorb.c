extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy_no_elemental(void);
extern void battle_calculate_hp_percent_damage(void);
extern void apply_hp_absorption(void);
void battle_formula_magic_hp_absorb(void) {
    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy_no_elemental() == 0) {
            battle_calculate_hp_percent_damage();
            apply_hp_absorption();
        }
    }
}
