extern void battle_calculate_hp_percent_damage(void);
extern void apply_hp_absorption(void);
extern void battle_apply_status(void);

/* Formula 0x47: absorb (Y)% of max HP, 100% status. */
void battle_formula_absorb_hp_y_percent_status(void) {
    battle_calculate_hp_percent_damage();
    apply_hp_absorption();
    battle_apply_status();
}
