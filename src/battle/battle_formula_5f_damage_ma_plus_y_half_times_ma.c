extern int calculate_magical_evade(void);
extern void battle_calculate_truth_formula_damage(void);

/* Formula 0x5F: damage ((MA + Y) / 2 * MA). */
void battle_formula_5f_damage_ma_plus_y_half_times_ma(void) {
    if (calculate_magical_evade() == 0) {
        battle_calculate_truth_formula_damage();
    }
}
