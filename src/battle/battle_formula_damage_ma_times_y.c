extern int calculate_magical_evade(void);
extern void battle_store_ma_and_y(void);
extern void battle_calculate_truth_magical_damage(void);

/* Formula 0x4E: damage (MA * Y). */
void battle_formula_damage_ma_times_y(void) {
    if (calculate_magical_evade() == 0) {
        battle_store_ma_and_y();
        battle_calculate_truth_magical_damage();
    }
}
