extern void battle_store_ma_and_y(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_calculate_magical_xa_times_ya(void);
extern void apply_faith_to_action_damage(void);
extern void apply_undead_reversal(void);

void battle_formula_magical_heal(void) {
    battle_store_ma_and_y();
    battle_apply_elemental_strengthen();
    battle_calculate_magical_xa_times_ya();
    apply_faith_to_action_damage();
    apply_undead_reversal();
}
