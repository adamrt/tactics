extern void battle_store_ma_and_ma_plus_y_divided_by_two(void);
extern void battle_calculate_truth_magical_damage(void);

void battle_calculate_truth_formula_damage(void) {
    battle_store_ma_and_ma_plus_y_divided_by_two();
    battle_calculate_truth_magical_damage();
}
