extern void calculate_katana_break_chance(void);
extern void battle_store_ma_and_y(void);
extern void battle_calculate_truth_magical_damage(void);

void battle_formula_draw_out_damage(void) {
    calculate_katana_break_chance();
    battle_store_ma_and_y();
    battle_calculate_truth_magical_damage();
}
