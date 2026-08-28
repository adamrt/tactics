extern int calculate_magical_evade(void);
extern void battle_store_ma_and_pa_plus_y_divided_by_two(void);
extern void battle_calculate_truth_magical_damage(void);

void battle_formula_ma_pa_half_damage(void) {
    if (calculate_magical_evade() == 0) {
        battle_store_ma_and_pa_plus_y_divided_by_two();
        battle_calculate_truth_magical_damage();
    }
}
