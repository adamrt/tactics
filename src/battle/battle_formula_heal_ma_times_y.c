extern void battle_store_ma_and_y(void);
extern void battle_calculate_magical_xa_times_ya(void);
extern void apply_undead_reversal(void);

/* Formula 0x4C: heal (MA * Y) HP. */
void battle_formula_heal_ma_times_y(void) {
    battle_store_ma_and_y();
    battle_calculate_magical_xa_times_ya();
    apply_undead_reversal();
}
