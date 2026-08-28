extern int calculate_magical_evade(void);
extern void battle_calculate_truth_formula_damage(void);

void battle_formula_multihit_truth_magic(void) {
    if (calculate_magical_evade() == 0) {
        battle_calculate_truth_formula_damage();
    }
}
