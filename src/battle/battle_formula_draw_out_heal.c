extern void calculate_katana_break_chance(void);
extern void battle_store_ma_and_y(void);
extern void battle_store_xa_times_ya_damage(void);
extern void apply_undead_reversal(void);

void battle_formula_draw_out_heal(void) {
    calculate_katana_break_chance();
    battle_store_ma_and_y();
    battle_store_xa_times_ya_damage();
    apply_undead_reversal();
}
